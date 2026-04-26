```mermaid
sequenceDiagram
    participant P as Publisher (RSS/Web)
    participant C as Crawler Worker
    participant K as Kafka (Raw Topic)
    participant F as Flink Stream Processor
    participant ML as ML Inference Service
    participant S3 as S3 (Raw HTML)
    participant DB as Cassandra (Metadata)
    participant R as Redis (Feed Cache)

    Note over P,C: adaptive polling triggers request
    P->>C: HTTP Response (HTML/XML)
    Note over C: Extract core text, Clean HTML
    C->>K: Produce Raw JSON (URL, Clean Text, Timestamp)
    
    Note over K,F: Near real-time consumption
    F->>F: Create unique Fingerprint (SimHash)
    
    F->>ML: POST /analyze (SimHash + Text)
    activate ML
    Note over ML: 1. NER (Entities)<br/>2. Bert Classification (Sports, etc)
    Note over ML: 3. Vector Search against<br/> recent SimHashes for dedup.
    ML-->>F: Response (Is_Duplicate=False, Category=Tech, Top_Story=True, Entities=[...])
    deactivate ML

    par Store Raw Content
        F->>S3: PUT raw_article.html
    and Store Metadata
        F->>DB: INSERT into articles_by_time<br/>(ID, Title, SimHash, Category, Entities, URL)
    end

    Note over F,R: If Top_Story or relevant to active topics
    F->>R: ZADD global_trending_feed [Score: Time, Value: Article_ID]
```
# The Ingestion Path: Pipeline & Component Deep Dive

The ingestion pipeline is a highly concurrent, asynchronous, and fault-tolerant system designed to ingest millions of news articles daily. Its primary goal is to fetch raw content, sanitize it, deduplicate it into cohesive "Story Clusters," categorize it using Machine Learning, and rapidly populate our caches for sub-100ms read access.

---

## 1. Adaptive Polling Scheduler & Crawler Workers

We cannot continuously poll 100,000 RSS feeds simultaneously without getting IP-banned or wasting immense compute resources on idle blogs. We use an **Adaptive Polling Strategy**.

*   **The Scheduler (Temporal / Cadence):** A distributed workflow engine maintains a schedule for every known news source.
*   **Dynamic Polling Frequency:** The polling interval is dynamically calculated based on historical publication frequency.
    *   *High-Volume Sources (e.g., Reuters, CNN):* Polled every 1 to 2 minutes.
    *   *Low-Volume Sources (e.g., niche tech blogs):* Polled every 4 to 12 hours.
*   **Crawler Workers (Go/Rust):** When the scheduler triggers a poll, an asynchronous worker grabs the task. It fetches the RSS XML or scrapes the seed URL, extracts the newly published URLs, and downloads the raw HTML payloads.

---

## 2. The Message Broker: Kafka Ingestion Topics

Crawler workers do not process the data; they simply dump it into a message broker to decouple fetching from heavy processing.

*   **Topic Name:** `raw_articles_ingestion`
*   **Partitioning Strategy:** Partitioned by `source_id`. This ensures that articles from the same publisher are processed sequentially, preventing race conditions if a publisher updates an article immediately after publishing it.
*   **Retention Policy:** 48 hours. This allows us to replay the stream and recover data if the downstream ML pipeline experiences a catastrophic failure.
*   **Message Schema (JSON):**
    ```json
    {
      "source_id": "uuid",
      "raw_url": "https://...",
      "html_payload": "<html>...",
      "fetched_at": "2024-05-20T12:00:00Z"
    }
    ```

---

## 3. Stream Processing Engine (Apache Flink)

Flink consumers continuously read from the Kafka partitions. Flink handles the heavy lifting of stateful stream processing.

*   **HTML Extraction:** Flink runs the raw HTML through a DOM parser (similar to Mozilla's Readability) to strip away ads, navbars, and boilerplate, extracting only the Title, Core Text, and Thumbnail URL.
*   **SimHash Generation:** Before invoking heavy ML models, Flink calculates a **SimHash** (a Locality-Sensitive Hash) of the core text. Unlike cryptographic hashes (SHA-256) where a single changed comma alters the entire hash, SimHash ensures that documents with similar text generate similar hashes (measured via Hamming distance).

---

## 4. Machine Learning Inference Service

Flink makes an asynchronous gRPC call to the ML Inference cluster (often deployed on GPU-backed Kubernetes pods) passing the clean text and the SimHash.

*   **Categorization (NLP):** We use a lightweight Transformer model (e.g., **fine-tuned DistilBERT**). It is fast enough for real-time inference and accurately multi-classifies the text into categories (e.g., `Technology`, `Sports`, `Politics`).
*   **Named Entity Recognition (NER):** A library like spaCy extracts key entities (e.g., "Elon Musk", "Tesla", "California") to populate metadata tags for search and finer personalization.
*   **Duplicate Detection:** The ML service queries an in-memory vector database (or Redis) containing the SimHashes of all articles published in the last 48 hours. If the Hamming distance between the new SimHash and an existing one is below a strict threshold `ε`, it flags the article as a **Duplicate**.

---

## 5. The Clustering Engine (Handling Duplicates)

When the ML service flags a duplicate, we do not discard the article. We group them into a **Story Cluster**.

*   **First Article (The Pioneer):** If no SimHash match is found, the article gets a newly generated `Cluster_ID`.
*   **Subsequent Articles:** If a match is found, the new article inherits the existing `Cluster_ID`.

### Selecting the Canonical "Head" Article
For every `Cluster_ID`, the system must elect a "Default" article to display in global feeds. Flink calculates a heuristic score for the incoming article:
$$Score = (W_1 \times Trust\_Factor) + (W_2 \times Media\_Richness) - (W_3 \times Time\_Decay)$$
*   **Trust Factor:** AP News gets a higher weight than a random blog.
*   **Media Richness:** Penalize articles missing thumbnails or clear snippets.
*   **Time Decay:** Reward the publisher who broke the story first.

If the new article's score is higher than the current Head Article of that `Cluster_ID`, it usurps the position and updates the metadata record as the primary representative of that story.

---

## 6. Polyglot Storage & Redis Involvement

Once Flink and the ML/Clustering engines have finalized the article metadata, the ingestion pipeline fans out the writes to our storage and cache layers.

1.  **Cold Storage (S3):** The raw HTML payload is dumped to S3 for compliance, legal disputes, and offline ML model retraining.
2.  **Persistent Metadata (Cassandra):** The enriched JSON (containing `Cluster_ID`, Category, Entities, Snippet, URL) is written to Cassandra (`Articles_By_Category`).
3.  **Hot Cache Population (Redis):** This is critical for the sub-100ms read requirement. The ingestion worker performs a write-through directly to Redis:
    *   **HSET (`article_meta:{article_id}`):** Stores the display metadata (Title, Snippet, Image) with a 7-day TTL.
    *   **ZSET (`category_feed:{category}`):** If the article is the Head of a Cluster, its `Cluster_ID` is pushed into the category's sorted set, scored by timestamp.
    *   **Event Trigger:** Finally, Flink drops a small `Article_Published` event into a secondary Kafka topic. The **Fan-Out Worker** consumes this to push the `Cluster_ID` into the pre-computed Redis feeds of active users who follow that category.
  
## 7. The Fan-out Feed Generation Worker (Personalization Push)

The Fan-out Worker bridges the gap between the ingestion pipeline and the user's lightning-fast read path. It is responsible for implementing the "Push" half of our Hybrid Push/Pull feed generation strategy. 

When a breaking news story is successfully processed and clustered, we need to deliver it to the customized feeds of users who care about it, without overwhelming the system.

### A. The Trigger
The worker listens to the `published_events` Kafka topic. The payload is lightweight, containing only the routing necessities:
```json
{
  "cluster_id": "cluster-999",
  "category": "Technology",
  "published_at": 1716200000,
  "ml_importance_score": 0.85
}
```
# Activity Tracking & The Fan-out Worker

To ensure our system scales, the Fan-out Worker must only push pre-computed feeds to "Active" users. Querying a massive PostgreSQL database to find active users matching a specific category on every single article publication would instantly melt the database under the read load. 

We decouple activity tracking from the primary relational database by utilizing an in-memory Redis cache.

---

## 1. The Core Concept: "Active Users by Category" Cache

Instead of a SQL query, the Fan-out Worker queries a dedicated set of **Redis Sorted Sets (ZSETs)** that act as an in-memory index of currently active users, segmented by the categories they follow.

*   **Key Pattern:** `active_subscribers:{category}` (e.g., `active_subscribers:technology`)
*   **Score:** The Unix Timestamp of the user's last API interaction.
*   **Value:** The `user_id`.

---

## 2. The "Activity Ping" (How it gets updated)

We do not execute heavy writes on every user click. Activity tracking is handled asynchronously to protect the read path.

1.  **The API Gateway:** Whenever a user interacts with the app (opens it, scrolls, clicks), the gateway validates their token and fires a lightweight, asynchronous "Activity Ping" event to a Kafka topic (e.g., `user_activity_logs`). 
    *   *Note: Pings are typically debounced at the client or gateway level (e.g., maximum one ping per user, per hour) to prevent flooding.*
2.  **The Activity Processor (Background Worker):** A lightweight consumer reads these pings.
3.  **Updating the Cache:** The processor looks up the user's followed categories and updates their timestamp in the relevant Redis ZSETs.
    *   **Command:** `ZADD active_subscribers:technology <current_unix_timestamp> <user_id>`
    *   Because `ZADD` is an $O(\log(N))$ operation, it updates the timestamp instantly without creating duplicate entries.

---

## 3. The Fan-out Execution (How it gets read)

When a new article is published and successfully clustered, the Fan-out Worker bypasses PostgreSQL entirely and goes straight to Redis.

1.  **The Query:** The worker asks Redis for all users in the specific category bucket whose score (timestamp) is strictly greater than 7 days ago.
    *   **Command:** `ZRANGEBYSCORE active_subscribers:technology <now_minus_7_days> +inf`
2.  **The Result:** Redis instantly returns a list of `user_ids` representing exactly the active cohort that needs their feed updated.
3.  **The Fan-out:** The worker takes this list, chunks it into batches of 1,000, and uses Redis Pipelining to push the new `Cluster_ID` into their individual `user_feed:{user_id}` ZSETs.

---

## 4. The Cleanup (Automatic Eviction)

To prevent the `active_subscribers` lists from growing infinitely and consuming all our RAM, cleanup is built directly into the Fan-out Worker's routine.

Immediately after the Fan-out Worker pulls the list of active users, it executes a cleanup command to drop anyone older than 7 days from the index:

*   **Command:** `ZREMRANGEBYSCORE active_subscribers:technology -inf <now_minus_7_days>`

### Summary of the Trade-off
By moving "Activity State" out of PostgreSQL and into time-scored Redis ZSETs segmented by category, we trade a small amount of RAM and background processing for massive read performance. The Fan-out Worker can identify hundreds of thousands of target users for a specific category in milliseconds, completely shielding the relational database from the fan-out storm.
