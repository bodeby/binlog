// bench/binlog/file/reader.cpp

#include <benchmark/benchmark.h>

#include "../fixtures.hpp"
#include "../schema.hpp"

#include <binlog/backend/file/reader.hpp>
#include <binlog/backend/file/writer.hpp>
#include <binlog/reader.hpp>
#include <binlog/writer.hpp>

#include <filesystem>

using bench::schema::Event;

namespace {

const std::filesystem::path Path{"benchmark-file-reader.bin"};

// Written from scratch on every run: reusing a file left over by
// another benchmark would decode a different event stream.
void create_file()
{
    const auto& events = bench::events();

    std::filesystem::remove(Path);

    binlog::backend::FileWriter backend(Path);
    binlog::Writer writer(std::move(backend));

    for (const auto& event : events)
        writer.write(event);

    writer.close();
}

} // namespace

// Decodes the whole event stream through the file backend. Opening the
// file is excluded from the measurement so only the decode path is
// timed.
static void BM_FileReader(benchmark::State& state)
{
    create_file();

    for (auto _ : state)
    {
        state.PauseTiming();

        binlog::backend::FileReader backend(Path);
        binlog::Reader reader(std::move(backend));

        state.ResumeTiming();

        std::size_t count = 0;

        while (auto event = reader.next<Event>())
        {
            benchmark::DoNotOptimize(event);
            ++count;
        }

        benchmark::DoNotOptimize(count);

        state.PauseTiming();

        reader.close();

        state.ResumeTiming();
    }

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(bench::EventCount));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(bench::EventCount * sizeof(Event)));
}

BENCHMARK(BM_FileReader);

BENCHMARK_MAIN();
