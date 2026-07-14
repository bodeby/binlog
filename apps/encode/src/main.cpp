// apps/encode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstdlib>
#include <filesystem>
#include <iostream>

// #include <binlog/backend/mmap.hpp>
#include <binlog/backend/file.hpp>
#include <binlog/writer.hpp>

using Side = encode::schema::Side;

int main() {

    encode::schema::FileHeader file_header{
        .magic = 1,
        .version = 1,
        .flags = 1,
        .startTimestamp = 1,
    };

    encode::schema::EventHeader header{
        .timestamp = 1,
        .size = 1,
        .version = 1,
    };

    encode::schema::EventBody payload{
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
    binlog::Writer writer(std::move(backend));

    writer.write(header);
    writer.write(payload);

    writer.flush();
    writer.close();

    return EXIT_SUCCESS;
}
