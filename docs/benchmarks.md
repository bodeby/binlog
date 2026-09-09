# Benchmarks

The benchmark suite lives in `bench/` and is built with
[Google Benchmark](https://github.com/google/benchmark). It is wired to
[CodSpeed](https://app.codspeed.io/bodeby/binlog), which re-runs it on every
push to `main` and on every pull request.

## Layout

| Executable                  | Source                            | What it measures                                            |
| --------------------------- | --------------------------------- | ----------------------------------------------------------- |
| `write_benchmark`           | `bench/binlog/base/write.cpp`     | Baseline: one unbuffered `write()` syscall per event         |
| `fwrite_buffered_benchmark` | `bench/binlog/base/fwrite_buffered.cpp` | Baseline: buffered `fwrite()` per event, no flushing   |
| `fwrite_flush_benchmark`    | `bench/binlog/base/fwrite_flush.cpp`    | Baseline: buffered `fwrite()` with a flush every N events |
| `file_writer_benchmark`     | `bench/binlog/file/writer.cpp`    | Capture path through the `FileWriter` backend                |
| `file_reader_benchmark`     | `bench/binlog/file/reader.cpp`    | Decode path through the `FileReader` backend                 |
| `mmap_writer_benchmark`     | `bench/binlog/mmap/writer.cpp`    | Capture path through the `MemoryMappedWriter` backend        |

Every benchmark replays the same deterministic event stream, generated once by
`bench/binlog/fixtures.hpp` and shared through `bench::events()`. Generation
happens outside the measured region, so only the write or decode path is timed.

The writer and reader benchmarks process `bench::EventCount` events per
iteration; the syscall-heavy baselines use a smaller batch so a single iteration
stays in the millisecond range.

## Running locally

Walltime numbers for a single executable (the way to compare against the tables
in the README):

```
make bench                       # defaults to file_writer_benchmark
make bench BENCH=mmap_writer_benchmark
```

The whole suite under CodSpeed's CPU simulation, which is what CI reports:

```
make bench-codspeed
```

That target configures the `codspeed` CMake preset
(`RelWithDebInfo` + `-DCODSPEED_MODE=simulation`), builds every benchmark
executable and runs them through the [CodSpeed CLI](https://codspeed.io/docs/cli).
Without the CLI the instrumented executables still run standalone, they simply
report `Checked:` instead of measuring.

## Adding a benchmark

1. Add the source file under `bench/binlog/<backend>/`.
2. Register an executable named `<something>_benchmark` in
   `bench/binlog/CMakeLists.txt` and link it against `benchmark::benchmark_main`
   (plus `binlog` if it exercises the library).
3. Reuse `bench::events()` for the input data and keep setup out of the
   measured region.

CI picks up any executable matching `*_benchmark`, so no workflow change is
needed.

## Notes on CPU simulation

CodSpeed runs the benchmarks once on a simulated CPU and reports instruction
level metrics instead of wall time. This removes CI noise, but it also means
syscall time is not part of the measurement: the `write()` baseline looks
cheaper than it is on real hardware. Use `make bench` for absolute throughput
numbers and CodSpeed for regression detection.
