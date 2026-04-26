```mermaid

flowchart LR
 subgraph Clients["Client Layer"]
        UserApp["Mobile/Web App"]
        Publisher["News Sources / RSS Feeds"]
  end
 subgraph Edge["Edge Layer"]
        CDN["CDN Images/Static Assets"]
        LB["Load Balancer & API Gateway"]
  end
 subgraph ReadPath["Read Path Services"]
        FeedServ["Feed Generation Service"]
        AnalServ["Analytics & Tracking Service"]
  end
 subgraph WritePath["Ingestion & Processing Pipeline"]
        Scheduler["Adaptive Polling Scheduler"]
        Crawler["Distributed Crawler/Fetcher Workers"]
        RawKafka["Kafka - Raw Articles Topic"]
        StreamProc["Stream Processing Engine Flink/Spark"]
        MLServ["ML Inference Service NLP/Dedup"]
  end
 subgraph DataStore["Polyglot Storage Layer"]
        S3["Object Storage Raw HTML"]
        Cassandra["NoSQL DB Article Metadata"]
        Postgres["RDBMS User Profiles/Source Meta"]
        Redis["Redis Cluster Feed & Metadata Cache"]
  end
    Publisher -- RSS/HTTP --> Crawler
    Scheduler -- Trigger --> Crawler
    Crawler -- Push Raw --> RawKafka
    RawKafka -- Consume --> StreamProc
    StreamProc <-- Categorize/Dedup --> MLServ
    StreamProc -- Store Content --> S3
    StreamProc -- Store Meta --> Cassandra
    StreamProc -- Invalidate/Populate --> Redis
    UserApp -- GET /feed --> CDN
    UserApp -- GET /feed API request --> LB
    LB --> FeedServ & AnalServ
    FeedServ -- User Prefs --> Postgres
    FeedServ -- "Pre-computed Feed" --> Redis
    FeedServ -- Fallback/Hydration --> Cassandra
    UserApp -- Beacon Click --> LB
    AnalServ -- Produce Event --> RawKafka
    RawKafka -- Process Signals --> StreamProc
    StreamProc -- Update User Profile --> Postgres

     UserApp:::external
     Publisher:::external
     RawKafka:::messaging
     S3:::storage
     Cassandra:::storage
     Postgres:::storage
     Redis:::storage
    classDef external fill:#f9f,stroke:#333,stroke-width:2px
    classDef storage fill:#ff9,stroke:#333,stroke-width:2px
    classDef messaging fill:#f96,stroke:#333,stroke-width:2px

```

# System Design: Real-Time News Aggregator

## 1. Deconstructing the Requirements
Before we draw a single box, let's look at our constraints.

### Functional Requirements
* **Ingestion:** Aggregate from thousands of RSS feeds and raw web crawls.
* **Consumption:** Real-time, personalized, infinite-scrolling feed.
* **Handoff:** Redirect users to the third-party publisher upon clicking an article.
* **Enrichment:** Automatically categorize news articles (e.g., Sports, Politics, Tech).

### Non-Functional Requirements
* **Speed:** Sub-100ms latency for fetching the news feed.
* **Resilience:** Highly available and scalable (expecting millions of Daily Active Users).

> **Senior Insight:**
> The "Redirect to third party" requirement is a massive architectural gift. It means we don't need to serve the full text of the article to the user. Our read path only needs to return metadata: `Title, Thumbnail, Snippet, Publisher, and the Source URL`.
> 
> This drastically shrinks our serving payload and cache memory requirements.

---

## 2. The Ingestion Pipeline: Catching the Firehose
Our system needs to ingest data from thousands of sources continuously. We cannot rely on a synchronous, monolithic scraper. We need a decoupled, asynchronous pipeline.

### The Architecture
* **Feed Fetcher / Crawler Service:** A distributed cluster of workers (e.g., built in Go for high concurrency) scheduled by a distributed cron system (like Airflow or Cadence). They poll RSS feeds or scrape designated seed URLs.
* **Raw Content Queue:** The fetchers dump the raw HTML/XML payloads into a message broker. **Apache Kafka** is the standard choice here due to its high throughput, durability, and support for replayability.
* **Processing Consumers:** Flink or Spark Streaming consumers read from Kafka to process the raw text.

#### Trade-off: Polling Frequency vs. System Load
> "Polling a small local blog every 5 minutes is a waste of resources, but polling CNN every hour means our 'real-time' system is woefully outdated."

**Decision:** Implement an **Adaptive Polling Schedule**. We track the publication frequency of each source. High-frequency sources (like Reuters) get polled every 1-2 minutes. Low-frequency sources get polled every few hours. We store this polling metadata in a fast RDBMS like PostgreSQL.

---

## 3. The Processing Engine: Making Sense of the Noise
Once we have the raw text, we must clean it, categorize it, and ensure we aren't showing the user the exact same story from five different publishers.

### Deduplication (The Near-Duplicate Problem)
News agencies often syndicate articles. Standard cryptographic hashes (like SHA-256) fail here because a single changed comma changes the entire hash.

* **Tech Choice:** SimHash or MinHash (Locality-Sensitive Hashing). These algorithms generate similar hashes for similar documents. If the Hamming distance between two hashes is below a certain threshold, we group them into a single "Story Cluster."

### Categorization & Enrichment
We pass the cleaned text through an NLP/ML service.

1. **Pipeline:** Extract keywords.
2. **NER:** Run Named Entity Recognition to find people and places.
3. **Classifier:** Use a fine-tuned BERT model to tag the article with categories (e.g., Tech, AI, Startups).

**Decision:** We only run heavy ML models asynchronously during ingestion, never on the user's read path. The output metadata is written to the database.

---

## 4. The Storage Layer: Polyglot Persistence
We have different access patterns for different types of data, which mandates a specific persistence strategy.

| Data Type | Tool | Purpose |
| :--- | :--- | :--- |
| **Raw Article Storage** | Amazon S3 | Compliance, model retraining, and debugging. |
| **Article Metadata** | Cassandra / DynamoDB | High write throughput and fast reads by ID. |
| **User Profiles & Graph** | PostgreSQL | Relational mapping of preferences and followed topics. |
| **Feed Cache** | Redis Cluster | Crucial for sub-100ms latency requirement. |

---

## 5. Feed Generation & Personalization
How do we generate a real-time, infinite-scrolling feed personalized to a user's tastes?

### The Winning Approach: Hybrid Model (Push + Pull)
* **Active Users:** For users who log in daily, we maintain a pre-computed "Home Feed" in Redis. We use an asynchronous worker that periodically updates this feed using a lightweight ML Ranking Model.
* **Inactive Users:** We do not pre-compute feeds for users who haven't logged in for a week. We generate their feed on the fly (Pull) upon their next login, caching it thereafter.
* **Global Popular News:** Breaking news is kept in a global Redis cache. The user's final feed is a quick merge of their **Personal Redis Feed + The Global Trending Feed**.

### Infinite Scrolling
* **Tech Choice:** **Cursor-based Pagination**. Offset-based pagination gets extremely slow for deep scrolls and suffers from duplicate items. Cursor-based pagination (using the article's timestamp) guarantees $O(1)$ performance.

---

## 6. The Serving Layer & Handoff
To achieve < 100ms latency:
1. **Client Request:** Hits the CDN (CloudFront) for static assets.
2. **API Gateway:** Handles rate-limiting and auth.
3. **Feed Service:** Fetches the pre-ranked list of Article IDs from Redis.
4. **Hydration:** Service fetches metadata (Title, Snippet, URL) from a secondary Redis cache.
5. **Response:** JSON payload returned to the user (~30-50ms).

### Handling Clicks (The Handoff)
1. **Redirect:** The client redirects the browser to the third-party URL.
2. **Analytics:** The client fires an asynchronous beacon event to our API.
3. **Processing:** A stream processor consumes this to update the article's CTR and the user's ML preference profile in the background.

---

## 7. Fault Tolerance & Resiliency
* **Ingestion Safety:** Rate limiting at the Ingestion Gateway per domain prevents rogue RSS sources from overwhelming the system.
* **Graceful Degradation:** If Redis goes down, the Feed Service falls back to Cassandra. Latency will spike to ~200ms, but the system remains available.
