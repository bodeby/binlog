// bench/binlog/mmap/writer.cpp

#include <benchmark/benchmark.h>

#include "../schema.hpp"

#include <binlog/backend/mmap/writer.hpp>
#include <binlog/writer.hpp>

#include <filesystem>
#include <random>
#include <vector>

using bench::schema::Event;
using bench::schema::Side;

namespace {

constexpr std::size_t EventCount = 1'000'000;

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
            .orderId      = i,
            .instrumentId = 1,
            .quantity     = qty_dist(rng),
            .price        = px_dist(rng),
            .side         = side_dist(rng) ? Side::Buy : Side::Sell,
        });
    }

    return events;
}

} // namespace

static void BM_MMAPWriter(benchmark::State& state)
{
    static const auto events = make_events();

    const std::filesystem::path path{"benchmark.bin"};

    for (auto _ : state)
    {
        state.PauseTiming();

        std::filesystem::remove(path);

        binlog::backend::MemoryMappedWriter backend(path);
        binlog::Writer writer(std::move(backend));

        state.ResumeTiming();

        for (const auto& event : events)
        {
            benchmark::DoNotOptimize(event);
            writer.write(event);
        }

        state.PauseTiming();

        writer.close();

        state.ResumeTiming();
    }

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(EventCount));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(EventCount * sizeof(Event)));
}

BENCHMARK(BM_MMAPWriter);

BENCHMARK_MAIN();
