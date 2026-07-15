# ROADMAP.md

# binlog Roadmap

The goal of this project is to build a production-quality binary logging library inspired by systems programming and High-Frequency Trading (HFT) workloads.

Each phase represents a complete, working milestone and should be tagged as a mini release.

---

# v0.1.0 — Binary Round Trip ✅

**Goal**

Prove that binary serialization works.

## Features

* Writer abstraction
* Reader abstraction
* FileWriter backend
* FileReader backend
* Binary serialization
* Binary deserialization
* Round-trip example application

## Deliverables

```
Writer
    ↓
events.bin
    ↓
Reader
```

Applications:

```
apps/
    encode/
    decode/
```

Success criteria

* Encode an event
* Decode the same event
* Values are identical

---

# v0.2.0 — Binary Format

**Goal**

Define and document the on-disk format.

## Features

* FileHeader
* EventHeader
* Magic number
* Versioning
* Payload size
* Documentation of binary layout

## Deliverables

```
+------------+
| FileHeader |
+------------+
| EventHeader|
+------------+
| Payload    |
+------------+
```

Documentation:

```
docs/
    format.md
```

Success criteria

* Binary format documented
* Decoder validates file magic/version

---

# v0.3.0 — Event API

**Goal**

Move binary metadata generation into the library.

Instead of

```cpp
writer.write(header);
writer.write(payload);
```

Users write

```cpp
writer.write(OrderSubmitted{...});
```

## Features

* Automatic FileHeader generation
* Automatic EventHeader generation
* Timestamp generation
* Payload size generation

Success criteria

* User never manually creates headers

---

# v0.4.0 — Event Registry

**Goal**

Support multiple event types.

## Features

* EventType enum
* Compile-time traits
* Event versioning
* Event registration

Example

```cpp
writer.write(OrderSubmitted{...});
writer.write(BookUpdate{...});
```

Success criteria

Reader can identify event types while decoding.

---

# v0.5.0 — mmap Backend

**Goal**

Implement a high-performance backend.

## Features

* mmap()
* munmap()
* ftruncate()
* Sequential writes
* Zero-copy append

Backends

```
FileWriter
FileReader

MemoryMappedWriter
MemoryMappedReader
```

Success criteria

Applications work without code changes by swapping backends.

---

# v0.6.0 — Inspection Tools

**Goal**

Make binary logs usable.

Applications

```
apps/
    inspect/
    dump/
    tail/
```

Examples

```
binlog-inspect events.bin
```

```
binlog-dump events.bin
```

```
binlog-tail events.bin
```

Success criteria

Binary logs become human-readable.

---

# v0.7.0 — Filtering & Search

**Goal**

Support live inspection.

Examples

```
binlog-tail events.bin
```

```
binlog-tail events.bin --event OrderSubmitted
```

```
binlog-tail events.bin --json
```

Success criteria

Can follow a running application in another terminal.

---

# v0.8.0 — Benchmarks

**Goal**

Measure performance.

Applications

```
bench/
```

Metrics

* Throughput
* Events/sec
* Latency
* File size
* CPU usage

Comparisons

* std::fstream
* mmap

Success criteria

README contains benchmark graphs.

---

# v0.9.0 — Ring Buffer

**Goal**

Separate application threads from disk I/O.

Architecture

```
Application
        │
        ▼
 Lock-Free Ring Buffer
        │
        ▼
 Background Writer
        │
        ▼
     Backend
```

Features

* Single Producer / Single Consumer
* Background flush thread
* Batched writes

Success criteria

Application never blocks on disk writes.

---

# v1.0.0 — Production Release

**Goal**

A polished binary logging framework.

## Features

* Stable binary format
* Versioned events
* File backend
* mmap backend
* Reader
* Writer
* Inspection tools
* Benchmarks
* Tests
* Documentation
* CI

Repository

```
include/
src/
apps/
bench/
tests/
docs/
```

Success criteria

A complete systems-programming portfolio project demonstrating:

* Binary serialization
* File formats
* Memory mapping
* Modern C++
* Generic programming
* Performance engineering
* Tooling
* Testing
* Documentation

---

# Future Ideas (Post v1.0)

These are intentionally out of scope for the initial release.

* Shared-memory backend
* Network streaming backend
* Compression
* Checksums
* Binary log replay
* JSON export
* Parquet export
* Python decoder
* Wireshark plugin
* Live TUI viewer
* Structured query language for logs
* Async io_uring backend (experimental)

These features should only be added if they clearly improve the project and do not compromise the simplicity of the core library.
