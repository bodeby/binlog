// bench/binlog/base/fwrite_buffered.cpp

#include <benchmark/benchmark.h>

#include "../schema.hpp"

#include <cstdio>
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

static void BM_FWrite(benchmark::State& state)
{
    static const auto events = make_events();

    FILE* file = std::fopen("benchmark-fwrite.bin", "wb");
    if (!file)
        state.SkipWithError("failed to open benchmark file");

    std::size_t index = 0;
    std::size_t writes = 0;

    const auto flush_interval =
        static_cast<std::size_t>(state.range(0));

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(events[index]);

        std::fwrite(&events[index], sizeof(Event), 1, file);

        if (++index == events.size())
            index = 0;

        if (++writes == flush_interval)
        {
            std::fflush(file);
            writes = 0;
        }
    }

    std::fflush(file);
    std::fclose(file);

    state.SetItemsProcessed(state.iterations());
    state.SetBytesProcessed(
        state.iterations() * static_cast<int64_t>(sizeof(Event)));
}

BENCHMARK(BM_FWrite)
    ->Arg(1)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000);

BENCHMARK_MAIN();
