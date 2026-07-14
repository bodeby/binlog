# Binlog

Binlog is a deterministic flight recorder for ultra–low-latency C++ systems. It captures structured binary events from hot-path code with constant-time cost and zero dynamic allocation.

Binlog is designed for environments such as high-frequency trading engines where logging must never introduce jitter, blocking, or hidden memory overhead. It is not a text logger and does not perform formatting in the hot path.

## Concept

Binlog follows a flight-recorder model:

* The hot path records fixed-size binary events.
* Events are written into a bounded single-producer/single-consumer ring buffer.
* A dedicated writer thread drains the buffer and persists records to disk.
* Formatting and human-readable interpretation happen offline.

This separation keeps capture deterministic and predictable.

## Design Goals

* No heap allocation in the producer path
* No locks in the producer path
* No syscalls in the producer path
* Constant-time event emission
* Bounded memory usage
* Cache-line aligned record layout
* C++20

## SBE inspired

* Fixed-size headers
* Versioned messages
* Sequential layout
* Little-endian encoding
* Zero-copy decoding where possible
* Cache-friendly structures
* Compile-time knowledge of layouts

## Architecture

Binlog runs as an embedded library inside the trading process.

### Producer (hot path):

* Emits fixed-size `Record` objects.
* Pushes them into a lock-free SPSC ring.
* Never blocks.
* Drops on overflow (configurable).

### Writer (cold path):

* Dedicated thread.
* Batches and writes raw binary records to file.
* May be pinned to a non-critical core.

There is no IPC and no side-car process in the default model.

## Example

Recording an event from hot-path code:

```cpp
recorder.record<EventId::OrderSent>(order_id, price, quantity);
```

This emits a structured binary record. No strings are formatted. No memory is allocated.

Records are decoded later using a separate tool.

## Non-Goals

* Text-based logging
* printf-style APIs
* Dynamic field formatting
* Multi-producer ring buffers
* Unbounded queues
* Runtime schema registration

## Build

Binlog requires a C++20-compatible compiler.

Typical build:

```
mkdir build
cd build
cmake ..
cmake --build .
```

The capture layer is header-first and can be embedded directly into latency-sensitive components. The writer and decoder are separate targets.

## License

MIT License.

## Audience

Binlog is intended for engineers building performance-critical systems such as:

* High-frequency trading engines
* Market data handlers
* Order gateways
* Real-time risk systems

If you need application-level logging, use a general-purpose logging library instead. Binlog is built for determinism and minimal interference with hot-path execution.
