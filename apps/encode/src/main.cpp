// apps/encode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstdlib>
#include <filesystem>
#include <iostream>

// #include <binlog/backend/mmap.hpp>
#include <binlog/backend/file.hpp>
#include <binlog/logger.hpp>

using Side = encode::schema::Side;

int main() {

    auto header = encode::schema::EventHeader{
        .timestamp = 1,
        .size = 1,
        .version = 1,
    };

    auto payload = encode::schema::EventBody{
        .orderId = 1,
        .instrumentId = 1,
        .quantity = 1,
        .price = 1,
        .side = Side::Sell,
    };

    std::clog << "px: " << payload.price << '\n';
    std::clog << "qty: " << payload.quantity << '\n';

    // setup logger;

    const auto path = std::filesystem::path("events.bin");
    binlog::backend::FileBackend backend(path);
    binlog::Logger logger(std::move(backend));

    logger.write(header);
    logger.write(payload);

    logger.flush();
    logger.close();

    return EXIT_SUCCESS;
}
