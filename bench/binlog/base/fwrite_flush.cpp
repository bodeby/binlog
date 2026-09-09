// bench/binlog/base/fwrite_flush.cpp

#include <benchmark/benchmark.h>

#include "../fixtures.hpp"
#include "../schema.hpp"

#include <cstdio>

using bench::schema::Event;

namespace {

const char* Path = "benchmark-fwrite-flush.bin";

// Smaller batch than the other benchmarks: flushing after every event
// turns each write into a syscall, which dominates the runtime.
constexpr std::size_t FlushBatch = 100'000;

} // namespace

// Baseline: buffered stdio writes with an explicit fflush() every
// `state.range(0)` events. Sweeping the flush interval shows how much
// durability costs on the write path.
static void BM_FWriteFlush(benchmark::State& state)
{
    const auto& events = bench::events();

    const auto interval = static_cast<std::size_t>(state.range(0));

    FILE* file = std::fopen(Path, "wb");
    if (!file)
    {
        state.SkipWithError("failed to open benchmark file");
        return;
    }

    for (auto _ : state)
    {
        std::rewind(file);

        std::size_t pending = 0;

        for (std::size_t i = 0; i < FlushBatch; ++i)
        {
            const auto& event = events[i];

            benchmark::DoNotOptimize(&event);
            std::fwrite(&event, sizeof(Event), 1, file);

            if (++pending == interval)
            {
                std::fflush(file);
                pending = 0;
            }
        }

        benchmark::ClobberMemory();
    }

    std::fflush(file);
    std::fclose(file);

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(FlushBatch));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(FlushBatch * sizeof(Event)));
}

BENCHMARK(BM_FWriteFlush)
    ->Arg(1)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000);

BENCHMARK_MAIN();
