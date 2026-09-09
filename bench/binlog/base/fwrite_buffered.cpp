// bench/binlog/base/fwrite_buffered.cpp

#include <benchmark/benchmark.h>

#include "../fixtures.hpp"
#include "../schema.hpp"

#include <cstdio>

using bench::schema::Event;

namespace {

const char* Path = "benchmark-fwrite-buffered.bin";

} // namespace

// Baseline: buffered stdio writes, one fwrite() per event and no
// explicit flushing. Every iteration writes the whole event stream so
// the measurement reflects steady-state throughput rather than a single
// call.
static void BM_FWriteBuffered(benchmark::State& state)
{
    const auto& events = bench::events();

    FILE* file = std::fopen(Path, "wb");
    if (!file)
    {
        state.SkipWithError("failed to open benchmark file");
        return;
    }

    for (auto _ : state)
    {
        std::rewind(file);

        for (const auto& event : events)
        {
            benchmark::DoNotOptimize(&event);
            std::fwrite(&event, sizeof(Event), 1, file);
        }

        benchmark::ClobberMemory();
    }

    std::fflush(file);
    std::fclose(file);

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(bench::EventCount));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(bench::EventCount * sizeof(Event)));
}

BENCHMARK(BM_FWriteBuffered);

BENCHMARK_MAIN();
