# ROADMAP.md

# binlog Roadmap

## Vision

`binlog` is a modern C++ library for serializing structured events into an append-only binary log.

The library focuses on:

* predictable performance
* simple abstractions
* type-safe serialization
* offline inspection and analysis

It intentionally **does not** provide threading, scheduling, queues, or telemetry frameworks. Those remain application responsibilities.

Every phase represents a stable milestone and should be tagged as a Git release.

---

# v0.1.0 — Binary Round Trip ✅

## Goal

Establish the core serialization pipeline.

## Features

* Writer
* Reader
* FileWriter
* FileReader
* Binary serialization
* Binary deserialization

Applications

```text
apps/
    encode/
    decode/
```

Success criteria

```text
Event

↓

Writer

↓

events.bin

↓

Reader

↓

Event
```

Decoded events exactly match the encoded events.

---

# v0.2.0 — Binary Format Specification

## Goal

Define a stable on-disk format.

## Features

* FileHeader
* EventHeader
* Magic number
* Version
* Payload size
* Endianness
* Alignment rules

Documentation

```text
docs/format.md
```

Success criteria

The binary format is fully documented and versioned.

---

# v0.3.0 — Event API

## Goal

Move serialization metadata into the library.

Instead of

```cpp
writer.write(header);
writer.write(payload);
```

users write

```cpp
writer.write(OrderSubmitted{...});
```

The library automatically generates

* FileHeader
* EventHeader
* timestamps
* payload size

Success criteria

Users only define events.

---

# v0.4.0 — Event Registry

## Goal

Support multiple event types.

## Features

* EventType
* compile-time event traits
* event versioning
* registry

Example

```cpp
writer.write(OrderSubmitted{...});
writer.write(BookUpdate{...});
writer.write(ThreadStart{...});
```

Success criteria

The Reader can identify event types without application-specific logic.

---

# v0.5.0 — Memory-Mapped Backend

## Goal

Provide a high-performance storage backend.

## Features

* mmap()
* munmap()
* ftruncate()
* sequential append
* zero-copy writes

Backends

```text
FileWriter
FileReader

MemoryMappedWriter
MemoryMappedReader
```

Success criteria

Switching backends requires no application changes.

---

# v0.6.0 — Inspection Tools

## Goal

Make binary logs easy to inspect.

Applications

```text
apps/
    inspect/
    dump/
    tail/
```

Examples

```bash
binlog-inspect events.bin
```

```bash
binlog-dump events.bin
```

```bash
binlog-tail events.bin
```

Success criteria

Binary logs become human-readable.

---

# v0.7.0 — Filtering & Export

## Goal

Support analysis workflows.

Examples

```bash
binlog-tail events.bin --event OrderSubmitted
```

```bash
binlog-tail events.bin --json
```

```bash
binlog-dump events.bin | jq
```

Features

* event filtering
* JSON output
* CSV output

Success criteria

Logs integrate naturally with standard Unix tooling.

---

# v0.8.0 — Performance

## Goal

Measure and understand performance.

Applications

```text
bench/
```

Metrics

* throughput
* events/sec
* latency
* binary size
* CPU usage

Comparisons

* FileWriter
* MemoryMappedWriter

Documentation

```text
docs/benchmarks.md
```

Success criteria

Performance claims are backed by reproducible benchmarks.

---

# v0.9.0 — Integration Examples

## Goal

Demonstrate how binlog fits into larger systems.

Examples

```text
Producer Thread
        │
        ▼
SPSC<Event>
        │
        ▼
Telemetry Thread
        │
        ▼
MemoryMappedWriter
```

Additional examples

* market data recorder
* matching engine telemetry
* replay application

Success criteria

Demonstrate that binlog composes naturally with external concurrency primitives instead of implementing them.

---

# v1.0.0 — Stable Release

## Goal

A complete binary event serialization library.

Features

[x] stable binary format
[x] versioned events
[x] File backend
[] MemoryMapped backend
[x] Reader
[x] Writer
[] inspection tools
[] benchmarks
[] tests
[] documentation
[] CI

Repository

```text
include/
src/
apps/
bench/
tests/
docs/
```

Success criteria

A polished systems programming project demonstrating

* binary serialization
* binary file formats
* memory mapping
* modern C++
* compile-time programming
* performance engineering
* tooling
* documentation
* testing

---

# Post v1.0

Possible future work

* compressed logs
* checksums
* binary replay engine
* Python decoder
* Parquet exporter
* shared-memory transport examples
* network transport examples
* terminal UI
* experimental io_uring backend

These are intentionally optional. The core library should remain small, focused, and composable.
