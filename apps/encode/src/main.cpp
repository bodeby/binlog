// apps/encode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <random>

#include <binlog/backend/file/writer.hpp>
#include <binlog/writer.hpp>

using Side = encode::schema::Side;

using binlog::detail::EventHeader;
using binlog::detail::FileHeader;
using encode::schema::EventBody;

int main() {

    std::cout << sizeof(FileHeader) << '\n';
    std::cout << sizeof(EventHeader) << '\n';
    std::cout << sizeof(EventBody) << '\n';

    // setup logger;

    const std::filesystem::path path{"events.bin"};
    binlog::backend::FileWriter backend(path);
    binlog::Writer writer(std::move(backend));

    constexpr std::uint32_t seed{42};
    std::mt19937 rng{seed};

    // random distributions
    std::uniform_int_distribution<std::uint32_t> qty_dist{1, 100};
    std::uniform_real_distribution<double> px_dist{-50, 50};
    std::bernoulli_distribution side_dist{0.5};

    constexpr std::uint64_t event_count{1000};
    constexpr std::uint64_t flush_interval{25};

    for (size_t i = 0; i < event_count; ++i) {
        writer.write(EventBody{
            .orderId = i,
            .instrumentId = 1,
            .quantity = qty_dist(rng),
            .price = px_dist(rng),
            .side = side_dist(rng) ? Side::Buy : Side::Sell,
        });

        // flush every 25 iterations
        if ((i + 1) % flush_interval == 0)
            writer.flush();
    }

    writer.close();
    return EXIT_SUCCESS;
}
