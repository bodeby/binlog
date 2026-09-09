// bench/binlog/fixtures.hpp

#pragma once

#include "schema.hpp"

#include <cstddef>
#include <random>
#include <vector>

namespace bench {

// Number of events processed by a single benchmark iteration.
constexpr std::size_t EventCount = 1'000'000;

// Deterministic event stream. The generator is seeded so every
// benchmark, iteration and machine observes the exact same payloads.
inline std::vector<schema::Event> make_events(std::size_t count = EventCount)
{
    using schema::Event;
    using schema::Side;

    std::mt19937 rng{42};

    std::uniform_int_distribution<std::uint32_t> qty_dist{1, 100};
    std::uniform_real_distribution<double> px_dist{-50.0, 50.0};
    std::bernoulli_distribution side_dist{0.5};

    std::vector<Event> events;
    events.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
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

// Shared event stream, built once on first use so that the generation
// cost never lands inside a measured region.
inline const std::vector<schema::Event>& events()
{
    static const std::vector<schema::Event> cache = make_events();
    return cache;
}

} // namespace bench
