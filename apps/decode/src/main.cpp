// apps/decode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstdlib>
#include <filesystem>

// library
#include <binlog/backend/file/reader.hpp>
#include <binlog/detail/format.hpp>
#include <binlog/reader.hpp>
#include <iostream>

using binlog::detail::FileHeader;
using binlog::detail::EventHeader;
using decode::schema::EventBody;

int main() {

    std::filesystem::path path("events.bin");
    binlog::backend::FileReader backend(path);

    binlog::Reader reader(std::move(backend));

    auto magic = reader.read<FileHeader>();
    auto header = reader.read<EventHeader>();
    auto body = reader.read<EventBody>();

    std::cout << "magic:         " << magic.magic << '\n';
    std::cout << "size:          " << magic.timestamp << '\n';
    std::cout << "version:       " << static_cast<int>(magic.version) << '\n';

    std::cout << "timestamp:     " << header.timestamp << '\n';
    std::cout << "size:          " << header.size << '\n';
    std::cout << "version:       " << static_cast<int>(header.version) << '\n';

    std::cout << "orderId:       " << body.orderId << '\n';
    std::cout << "instrumentId:  " << body.instrumentId << '\n';
    std::cout << "quantity:      " << body.quantity << '\n';
    std::cout << "price:         " << body.price << '\n';
    std::cout << "side:          " << static_cast<int>(body.side) << '\n';

    reader.close();

    return EXIT_SUCCESS;
}
