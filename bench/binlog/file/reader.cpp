// bench/binlog/file/reader.cpp

#include <benchmark/benchmark.h>

#include "../schema.hpp"

#include <binlog/backend/file/reader.hpp>
#include <binlog/backend/file/writer.hpp>
#include <binlog/reader.hpp>
#include <binlog/writer.hpp>

#include <filesystem>
#include <random>
#include <vector>

using bench::schema::Event;
using bench::schema::Side;

namespace {

constexpr std::size_t EventCount = 1'000'000;
const std::filesystem::path Path{"benchmark.bin"};

std::vector<Event> make_events()
{
    std::mt19937 rng{42};

    std::uniform_int_distribution<std::uint32_t> qty_dist{1, 100};
    std::uniform_real_distribution<double> px_dist{-50.0, 50.0};
    std::bernoulli_distribution side_dist{0.5};

    std::vector<Event> events;
    events.reserve(EventCount);

    for (std::size_t i = 0; i < EventCount; ++i)
    {
        events.push_back({
            .orderId = i,
            .instrumentId = 1,
            .quantity = qty_dist(rng),
            .price = px_dist(rng),
            .side = side_dist(rng) ? Side::Buy : Side::Sell,
        });
    }

    return events;
}

void create_file()
{
    if (std::filesystem::exists(Path))
        return;

    auto events = make_events();

    binlog::backend::FileWriter backend(Path);
    binlog::Writer writer(std::move(backend));

    for (const auto& event : events)
        writer.write(event);

    writer.close();
}

} // namespace

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

        reader.close();
    }

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(EventCount));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(EventCount * sizeof(Event)));
}

BENCHMARK(BM_FileReader);

BENCHMARK_MAIN();
