# Latch

Latch is a zero-allocation, lock-free binary event recorder designed for ultra–low-latency trading systems. It is not a traditional logging library. It is a deterministic flight recorder for hot-path code.

The library is built for environments where latency, predictability, and bounded memory behavior are mandatory. It avoids dynamic allocation, string formatting, locks, and syscalls in the producer path. Events are written as fixed-size binary records and decoded offline.

## Purpose

Latch exists to record critical runtime events in high-frequency trading systems without disturbing the execution characteristics of the hot path.

It is suitable for:

* Strategy kernels pinned to dedicated cores
* Market data handlers
* Order routing engines
* Risk modules requiring deterministic instrumentation
* Any system where logging must never block

It is not intended for general application logging.

Design Principles

Hot path must be deterministic:

* No heap allocations
* No locks
* No syscalls
* No formatting
* Constant-time event emission

Events are:

* Fixed-size
* Plain-old-data
* Cache-line aligned
* Written to a bounded SPSC ring buffer

A dedicated cold thread consumes events and persists them to disk. Formatting and human-readable decoding are performed offline using a separate tool.

Architecture

Producer (hot path):

* Emits a fixed-size LogEvent
* Pushes to a lock-free SPSC ring
* Never blocks
* Drops on overflow (configurable)

Consumer (cold path):

* Drains ring
* Writes batched binary records to file
* Optional mmap-backed writer

Decoder tool:

* Reads raw binary log
* Maps EventId to readable output
* Converts TSC to wall-clock time (optional)

Why Not Use a Traditional Logger?

String formatting, heap allocation, and IO calls introduce jitter and non-deterministic latency. Even “fast” logging libraries are not designed for the strict constraints of ultra-HFT hot paths.

Latch separates event capture from presentation. The hot path records structured data only. Interpretation happens later.

Feature Overview

* C++20
* Header-first hot path API
* Lock-free SPSC ring buffer
* Compile-time event identifiers
* Fixed-size binary event layout
* Zero dynamic allocation in producer
* Drop-on-overflow policy
* Offline decoding tool
* Optional TSC-based timestamping

Non-Goals

* Text logging in the hot path
* printf-style APIs
* Dynamic field formatting
* Unbounded queues
* Multi-producer ring buffers
* Runtime schema registration

Example

Hot path usage:

```
log<EventId::OrderSent>(order_id, price, quantity);
```

This records a structured binary event with constant-time cost. No strings are formatted. No memory is allocated.

A separate decoding tool converts the binary log into human-readable output.

Build

Latch requires a C++20-compatible compiler.

Typical build:

```
mkdir build
cd build
cmake ..
cmake --build .
```

Integration

The hot path component can be included header-only. The runtime writer and decoder are separate targets.

Only the core headers are required for producer-side integration.

License

Latch is released under the MIT License.

Intended Audience

This library targets engineers building latency-sensitive systems such as:

* High-frequency trading engines
* Market making infrastructure
* Exchange gateways
* Real-time financial data systems

If your primary concern is application-level logging, consider using a general-purpose logging library instead.

Latch is built for determinism first.
