// bench/binlog/mmap/writer.cpp

#include <benchmark/benchmark.h>

#include "../fixtures.hpp"
#include "../schema.hpp"

#include <binlog/backend/mmap/writer.hpp>
#include <binlog/writer.hpp>

#include <filesystem>

using bench::schema::Event;

namespace {

const std::filesystem::path Path{"benchmark-mmap-writer.bin"};

} // namespace

// Writes the whole event stream through the memory mapped backend.
// Mapping the file and syncing it on close are excluded from the
// measurement so only the hot path is timed.
static void BM_MMAPWriter(benchmark::State& state)
{
    const auto& events = bench::events();

    for (auto _ : state)
    {
        state.PauseTiming();

        std::filesystem::remove(Path);

        binlog::backend::MemoryMappedWriter backend(Path);
        binlog::Writer writer(std::move(backend));

        state.ResumeTiming();

        for (const auto& event : events)
        {
            benchmark::DoNotOptimize(&event);
            writer.write(event);
        }

        benchmark::ClobberMemory();

        state.PauseTiming();

        writer.close();

        state.ResumeTiming();
    }

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(bench::EventCount));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(bench::EventCount * sizeof(Event)));
}

BENCHMARK(BM_MMAPWriter);

BENCHMARK_MAIN();
