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

    encode::schema::EventBody payload{
        .orderId = 1,
        .instrumentId = 2,
        .quantity = 3,
        .price = 4,
        .side = Side::Sell,
    };

    std::clog << "px: " << payload.price << '\n';
    std::clog << "qty: " << payload.quantity << '\n';

    // setup logger;

    const auto path = std::filesystem::path("events.bin");
    binlog::backend::FileWriter backend(path);
    binlog::Writer writer(std::move(backend));

    writer.write(payload);

    writer.flush();
    writer.close();

    return EXIT_SUCCESS;
}
