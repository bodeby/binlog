// bench/binlog/file/writer.cpp

#include <benchmark/benchmark.h>

#include "../fixtures.hpp"
#include "../schema.hpp"

#include <binlog/backend/file/writer.hpp>
#include <binlog/writer.hpp>

#include <filesystem>

using bench::schema::Event;

namespace {

const std::filesystem::path Path{"benchmark-file-writer.bin"};

} // namespace

// Writes the whole event stream through the file backend. Opening the
// file and flushing it on close are excluded from the measurement so
// only the hot path is timed.
static void BM_FileWriter(benchmark::State& state)
{
    const auto& events = bench::events();

    for (auto _ : state)
    {
        state.PauseTiming();

        std::filesystem::remove(Path);

        binlog::backend::FileWriter backend(Path);
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

BENCHMARK(BM_FileWriter);

BENCHMARK_MAIN();
