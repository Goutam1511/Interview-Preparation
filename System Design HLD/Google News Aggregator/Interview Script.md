# System Design Interview Script: Google News Aggregator

**Role:** Senior Backend/Distributed Systems Engineer
**Duration:** 45-60 Minutes
**Format:** Whiteboard / Virtual Drawing Tool

---

## Part 1: Requirements Gathering & Scoping (Minutes 0-10)

**Interviewer:** Thanks for joining today. I'd like you to design a news aggregator system, similar to Google News or Apple News. It needs to pull in news from thousands of publishers and serve a personalized feed to users. How would you approach this?

**Candidate:** Great. Let's lock down the scope. I assume we have functional requirements like ingesting RSS/web crawls, generating a personalized infinite-scroll feed, and categorizing the news. Are we hosting the full article text, or just redirecting users?

**Interviewer:** Just redirecting. When they click, they go to the publisher's site.

**Candidate:** Excellent, that vastly simplifies our read payload and storage constraints. What about Non-Functional Requirements? What scale are we looking at?

**Interviewer:** Assume 50 million Daily Active Users (DAU). We ingest from about 50,000 sources globally. For latency, the feed must load in under 100ms. 

**Candidate:** 50M DAU with sub-100ms latency means our read path must be heavily cached and decoupled from any heavy compute. 50,000 sources means ingestion is highly concurrent. I'll split this into two isolated systems: an asynchronous write-heavy **Ingestion Pipeline** and a synchronous read-heavy **Serving Layer**.

---

## Part 2: The Ingestion Pipeline & Deduplication (Minutes 10-25)

**Candidate:** Let's start with ingestion. I wouldn't use a monolithic scraper. I'll use an **Adaptive Polling Scheduler** (like Cadence or Temporal) that triggers distributed Go workers to fetch RSS feeds. A major news outlet gets polled every minute; a local blog every 6 hours.

**Interviewer:** Makes sense. Where does the data go once fetched? 

**Candidate:** The workers drop the raw HTML into a Kafka topic, partitioned by `source_id` to maintain ordering per publisher. A stream processor, like Apache Flink, consumes this. Flink extracts the text and metadata.

**Interviewer:** Let me stop you there. When a major event happens, say an election result, 500 publishers will post the exact same story within five minutes. How do you prevent the user's feed from being 50 identical articles?

**Candidate:** We need a deduplication strategy, but standard cryptographic hashes like SHA-256 won't work because minor text differences (like a changed comma) change the whole hash. I'll use a Locality-Sensitive Hash, specifically **SimHash**. Flink generates a SimHash for the text. We compare it against recent articles via an ML vector search. If the Hamming distance is below a tight threshold `ε`, it's a duplicate.

**Interviewer:** So do we throw the duplicate away?

**Candidate:** No, storage is cheap and we need that data for publisher attribution and ML training. Instead, we group them. The first article generates a new `Cluster_ID`. All subsequent duplicates are assigned that same `Cluster_ID`. We only show one article per `Cluster_ID` in the feed.

---

## Part 3: Data Layer & Personalization Fan-Out (Minutes 25-35)

**Interviewer:** Let's talk about the database. What are you storing this metadata in, and how are you building the personalized feeds?

**Candidate:** I'll use **Cassandra** (or DynamoDB) for the core metadata storage. It handles the massive write throughput of continuous news ingestion perfectly. The partition key will be `category#date` and the sort key `published_at` to support fast time-series queries.

For the feeds, to hit that sub-100ms latency, we cannot query Cassandra on the read path. I'll use **Redis Sorted Sets (ZSETs)**. We'll have a `global_trending` feed and individual `user_feed:{user_id}` feeds.

**Interviewer:** If a breaking "Technology" article drops, do you fan it out to every user who follows "Technology"? With 50M DAU, that sounds like a write amplification nightmare.

**Candidate:** Exactly. That's the classic "Justin Bieber problem" in fan-out architectures. To solve this, the Fan-out Worker will *only* push to "Active Users." 

**Interviewer:** How does it know who is active without querying a 50M row Postgres table every second?

**Candidate:** We use Redis for activity tracking too. We maintain ZSETs like `active_subscribers:technology` where the score is the timestamp of their last API ping. The Fan-out worker simply does a `ZRANGEBYSCORE` to grab users active in the last 7 days, batches them, and pipelines the updates to their pre-computed feeds. Inactive users get built on-the-fly when they next log in.

**Interviewer:** Very nice. And what exactly are you pushing to the `user_feed` ZSET?

**Candidate:** The score is the ML ranking weight, and the value is the `Cluster_ID`—*not* the `Article_ID`. 

**Interviewer:** Why the `Cluster_ID`?

**Candidate:** **Late Binding**. If we push the `Article_ID`, we lock the user into whichever publisher broke the story first. By storing the `Cluster_ID`, the Serving Layer can dynamically resolve the cluster into an `Article_ID` at read-time, matching the story against the user's personal Publisher Affinity graph. User A gets the NYT version, User B gets the Reuters version.

---

## Part 4: The Read Path & Resiliency (Minutes 35-45)

**Interviewer:** Let's walk through the read API. A user opens the app. Trace the request.

**Candidate:** The client hits the API Gateway, which handles rate limiting and passes the request to the Feed Service. The service queries Redis: `ZREVRANGE user_feed:{user_id} 0 20`. It gets 20 `Cluster_IDs`, resolves them to `Article_IDs` based on affinities, and then does an `MGET` against a Redis Hash (`article_meta:{id}`) to hydrate the titles, snippets, and thumbnail URLs. It packages this as JSON and returns it. Total latency should be around 30-40ms.

**Interviewer:** What if the Redis cluster holding the pre-computed feeds completely crashes and OOMs right now?

**Candidate:** We implement graceful degradation. The Feed Service's circuit breaker trips on Redis timeouts. It falls back to querying Cassandra directly. We lose the deep ML personalization temporarily, defaulting to a basic chronological query of the user's followed categories. Latency spikes to maybe 200ms, but the system stays highly available. We'll also rely heavily on the CDN to serve slightly stale feeds to absorb the thundering herd while Redis restarts.

**Interviewer:** Excellent. We are out of time, but this looks like a solid, highly scalable architecture.
