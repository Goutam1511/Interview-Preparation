# System Design: Document Upload and Review System (HLD)

## 1. Overview & High-Level Architecture

### Core Requirements
**Functional:**
1. Users upload documents of any size.
2. Internal audit team manually reviews the documents.
3. Internal audit team receives notifications when a document review deadline approaches.
4. Customers are notified of the review outcome (Approved/Rejected).
5. Customers can re-upload or cancel reviews based on outcomes.

**Non-Functional:**
1. **High Scalability & Availability:** Must handle massive file uploads without degrading application server performance.
2. **Fault Tolerance:** System must not lose documents or drop notifications.

### MVP Architecture Diagram
```mermaid
graph TD
    subgraph Clients
        Cust[Customer Portal]
        Aud[Internal Audit Portal]
    end

    APIG[API Gateway / Load Balancer]

    Cust -->|HTTPS Request| APIG
    Aud -->|HTTPS Request| APIG

    subgraph Core Services
        DS[Document Service]
        WS[Workflow & State Service]
        NS[Notification Service]
        Sched[Deadline Scheduler]
    end

    APIG --> DS
    APIG --> WS

    %% Upload Flow
    Cust -.->|Direct Upload via Presigned URL| S3[(Object Storage - AWS S3)]
    DS -->|Generates URL| S3
    S3 -->|S3 Event trigger| MQ[Message Broker - Kafka/SQS]
    MQ -->|Upload Complete Event| WS

    %% Data layer
    DS --> PrimaryDB[(PostgreSQL - Primary)]
    WS --> PrimaryDB
    PrimaryDB -.-> ReadReplica[(PostgreSQL - Replica)]
    Sched -->|Polls for Deadlines| ReadReplica

    %% Async & Comms
    WS -->|Review/Deadline Events| MQ
    MQ --> NS
    Sched -->|Triggers Deadline Logic| WS
    NS --> Ext[Email / SMS / Push]

    classDef service fill:#f9f,stroke:#333,stroke-width:2px;
    class DS,WS,NS,Sched service;
```

## 2. Component Deep Dive & Core Workflows

---

### Core Components

* **API Gateway**: Handles authentication, rate limiting, and routes requests to appropriate backend services.
* **Document Service**: Responsible for file metadata and orchestrating the upload process. Crucially, it **does not process the file bytes directly**, which protects the system from memory exhaustion and network bottlenecks.
* **Object Storage (AWS S3 / GCS)**: Stores the actual document blobs. Highly scalable, durable, and natively supports large files and multipart uploads.
* **Workflow & State Service**: The "state machine" of the system. It tracks the lifecycle of a document (e.g., `PENDING_UPLOAD`, `IN_REVIEW`, `APPROVED`, `REJECTED`, `CANCELED`).
* **Deadline Scheduler**: Constantly checks for documents approaching their SLA/deadline and triggers alerts via the notification system.
* **Message Broker (Kafka / SQS)**: Decouples services. Used for asynchronous event processing (e.g., notifying the system when an S3 upload finishes, or queuing emails).
* **Notification Service**: Listens to events from the message broker and formats them into emails, in-app notifications, or Slack messages for both customers and internal auditors.

---

### Core Workflows

#### A. Handling "Any Size" Document Uploads
Passing huge files (e.g., 5GB PDFs or zips) through backend application servers causes network saturation and out-of-memory (OOM) errors. We solve this using the **Presigned URL pattern**:

1.  **Client** calls `POST /documents` with metadata (filename, size).
2.  **Document Service** creates a DB record with status `PENDING_UPLOAD`.
3.  **Document Service** requests a Presigned URL from S3 and returns it to the client.
4.  **Client** uploads the file bytes directly to S3 using the URL.
5.  **S3** fires an event to the Message Broker upon successful upload.
6.  **Workflow Service** consumes the event, updates the DB status to `IN_REVIEW`, and sets the `deadline_at` timestamp.

#### B. Deadline Tracking System
To efficiently track deadlines among millions of documents:

1.  We index the `documents` table on `(status, deadline_at)`.
2.  The **Deadline Scheduler** queries the Read Replica:
    ```sql
    SELECT id 
    FROM documents 
    WHERE status = 'IN_REVIEW' 
      AND deadline_at <= NOW() + INTERVAL '24 HOURS' 
      AND deadline_notified = FALSE;
    ```
3.  It drops these document IDs into a **Kafka topic**.
4.  The **Notification Service** picks them up and alerts the audit team.

## 3. Detailed API Specifications

The APIs follow **RESTful principles**, utilizing JSON payloads and standard HTTP status codes.

---

### 3.1. Customer API: Initialize Document Upload
Initializes the upload process and generates a Presigned URL.

* **Endpoint:** `POST /api/v1/documents`
* **Headers:** `Authorization: Bearer <Customer_Token>`

**Request Body:**
```json
{
  "file_name": "employee_passport_2026.pdf",
  "file_size_bytes": 10485760,
  "document_type": "IDENTIFICATION",
  "mime_type": "application/pdf"
}
```
**Response (201 Created):**
```json
{
  "data": {
    "document_id": "d-8f7b2a9c-11e2",
    "status": "PENDING_UPLOAD",
    "upload_url": "[https://rippling-docs.s3.amazonaws.com/...&X-Amz-Signature=](https://rippling-docs.s3.amazonaws.com/...&X-Amz-Signature=)...",
    "upload_expires_in_seconds": 3600
  }
}
```
### 3.2. Customer API: Get Document Status
* **Endpoint:** `GET /api/v1/documents/{document_id}`
* **Headers:** `Authorization: Bearer <Customer_Token>`

**Response (200 OK):**

```json
{
  "data": {
    "document_id": "d-8f7b2a9c-11e2",
    "status": "APPROVED",
    "deadline_at": "2026-05-01T12:00:00Z",
    "review_comments": "All looks good.",
    "updated_at": "2026-04-27T10:15:00Z"
  }
}
```
### 3.3. Customer API: Re-upload / Rectify Document
Used when a document is rejected and the customer needs to upload a corrected version.

* **Endpoint:** `POST /api/v1/documents/{document_id}/reupload`

* **Headers:** `Authorization: Bearer <Customer_Token>`

**Request Body:**

```json
{
  "file_name": "employee_passport_2026_corrected.pdf",
  "file_size_bytes": 12000000,
  "mime_type": "application/pdf"
}
```
**Response (200 OK):**

```json
{
  "data": {
    "document_id": "d-8f7b2a9c-11e2",
    "status": "PENDING_UPLOAD",
    "upload_url": "[https://rippling-docs.s3.amazonaws.com/...(new_url)](https://rippling-docs.s3.amazonaws.com/...(new_url))",
    "message": "Previous file invalidated. Please upload the new file."
  }
}
```
### 3.4. Internal Audit API: Fetch Queue
Fetches a list of documents pending review, sorted by approaching deadlines.

* **Endpoint:** `GET /api/internal/documents`
* **Query Parameters:** `?status=IN_REVIEW&sort_by=deadline_at:asc&limit=50`
* **Headers:** `Authorization: Bearer <Auditor_Token>`

**Response (200 OK):**

```json
{
  "data": [
    {
      "document_id": "d-12345678",
      "document_type": "W4_FORM",
      "status": "IN_REVIEW",
      "deadline_at": "2026-04-28T10:00:00Z",
      "time_remaining_hours": 24
    }
  ]
}
```
### 3.5. Internal Audit API: Submit Review
Submits the final decision on a document. This API is idempotent.

* **Endpoint:** `POST /api/internal/documents/{document_id}/reviews`

* **Headers:** `Authorization: Bearer <Auditor_Token>`

**Request Body:**

```json
{
  "outcome": "REJECTED",
  "comments": "The signature on page 2 is missing. Please sign and re-upload.",
  "auditor_id": "a-554433"
}
```

**Response (201 Created):**

```json
{
  "data": {
    "document_id": "d-12345678",
    "status": "REJECTED",
    "review_id": "r-999888",
    "message": "Review submitted successfully. Customer will be notified."
  }
}
```


# 5. Architecture Decisions & Trade-offs

This section outlines the critical design choices made for the Document Lifecycle system, comparing alternative approaches and detailing the final decisions based on scalability and compliance requirements.

---

## Trade-off 1: Cron Scheduler vs. Distributed Workflow Orchestrator (Temporal)

**Where it fits:** Deadline Scheduler and Workflow & State Service.

### The Problem
Documents have a strict "time to review" (SLA). We need a reliable mechanism to trigger an alert exactly 24 hours before the deadline expires.

### Approach A: Cron Job + DB Polling (Simpler)
* **Design**: A scheduled worker runs every 5 minutes and queries the Read Replica.
    ```sql
    SELECT id FROM documents 
    WHERE deadline < NOW() + INTERVAL '24 HOURS' 
    AND status = 'IN_REVIEW' 
    AND deadline_notified = FALSE;
    ```
* **Pros**: Easy to build; utilizes standard infrastructure (Postgres, Cron).
* **Cons**: Scaling issues with millions of rows; potential for missed windows if the job crashes; creates "thundering herd" spikes on the database every 5 minutes.

### Approach B: Distributed Orchestrator (Temporal/Cadence)
* **Design**: When a document enters `IN_REVIEW`, a stateful workflow starts. The logic uses a durable timer: `sleep(deadline - 24 hours); sendNotification();`.
* **Pros**: Extremely scalable; handles millions of concurrent timers; implicit retries and state persistence.
* **Cons**: High operational overhead to maintain a Temporal cluster.

**Conclusion**: For a startup, **Approach A** is sufficient. For a massive enterprise like Rippling with strict compliance SLAs, **Approach B** is the standard and replaces the standalone Deadline Scheduler entirely.

---

## Trade-off 2: Client-side Polling vs. Server-Sent Events (SSE)

**Where it fits**: Connection between the Customer Portal (Client) and API Gateway.

### The Problem
Since the client uploads massive files directly to S3, the browser needs a way to know when the backend has successfully processed the S3 event and updated the document status to `IN_REVIEW`.

### Approach A: Client Polling
* **Design**: The frontend calls `GET /api/v1/documents/{id}` every 3 seconds until the status changes.
* **Pros**: Simplest to implement; stateless backend.
* **Cons**: Wasteful network traffic; can overload the API Gateway and Database with redundant read requests.

### Approach B: Server-Sent Events (SSE)
* **Design**: The client establishes a one-way SSE connection. When the Workflow Service processes the Kafka event from S3, it pushes the update directly to the client.
* **Pros**: Immediate updates; superior UX; significantly lower API and DB load.
* **Cons**: Requires persistent connections; slightly more complex load balancing.

**Conclusion**: **Use SSE**. It is perfectly suited for one-way server-to-client notifications (unlike the overhead of bi-directional WebSockets) and drastically reduces system-wide load.

---

## Trade-off 3: Ensuring Fault Tolerance with Dead Letter Queues (DLQs)

**Where it fits**: Between the Message Broker (Kafka/SQS) and the Notification Service.

### The Problem
If a 3rd-party provider (e.g., SendGrid) is down, we cannot afford to lose critical approval or rejection notifications.

### Implementation Strategy: At-Least-Once Delivery
1.  The **Notification Service** consumes a message from the broker.
2.  If the email fails to send, the message is **not** acknowledged.
3.  The broker retries with **exponential backoff** (e.g., 1m, 5m, 15m).
4.  After 5 failed attempts, the message is moved to a **Dead Letter Queue (DLQ)**.
5.  **Engineering Alerts**: DLQ activity triggers a PagerDuty alert for manual intervention to ensure no notification is lost.

---

## Trade-off 4: Data Deletion Strategy (Soft vs. Hard Deletes)

**Where it fits**: Primary Database and Object Storage (S3).

### The Problem
Handling "Cancel Review" requests or document rejections in a way that balances user privacy with regulatory compliance.

### Implementation Strategy
In the HR and Compliance domain, immediate hard deletion is risky due to accidental clicks and the necessity of audit trails.

* **Database (PostgreSQL)**: We use **Soft Deletes**. Rows are updated to `status = 'CANCELED'` with a timestamp. This preserves the audit trail for compliance teams.
* **Object Storage (S3)**: We utilize **S3 Lifecycle Policies**.
    * **30 Days**: Move canceled/rejected files to a cheaper tier (**S3 Glacier**).
    * **90 Days**: Permanently **Hard-Delete** the files to remain compliant with GDPR/CCPA "Right to Erasure" regulations.
