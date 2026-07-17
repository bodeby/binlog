// apps/encode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstdlib>
#include <filesystem>
#include <iostream>

// #include <binlog/backend/mmap.hpp>
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

    const auto path = std::filesystem::path("events.bin");
    binlog::backend::FileWriter backend(path);
    binlog::Writer writer(std::move(backend));

    writer.write(EventBody{
        .orderId = 1,
        .instrumentId = 2,
        .quantity = 3,
        .price = 4,
        .side = Side::Sell,
    });

    writer.write(EventBody{
        .orderId = 2,
        .instrumentId = 2,
        .quantity = 7,
        .price = 3,
        .side = Side::Buy,
    });

    writer.write(EventBody{
        .orderId = 3,
        .instrumentId = 2,
        .quantity = 10,
        .price = 5,
        .side = Side::Sell,
    });

    writer.flush();
    writer.close();

    return EXIT_SUCCESS;
}
