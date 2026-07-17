// apps/decode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstdlib>
#include <filesystem>
#include <iostream>

// library
#include <binlog/backend/file/reader.hpp>
#include <binlog/detail/format.hpp>
#include <binlog/reader.hpp>

using binlog::detail::EventHeader;
using binlog::detail::FileHeader;
using decode::schema::EventBody;

int main() {

    std::filesystem::path path("events.bin");
    binlog::backend::FileReader backend(path);

    binlog::Reader reader(std::move(backend));
    const auto& file_header = reader.fileheader();

    std::cout << "magic:         " << file_header.magic << '\n';
    std::cout << "size:          " << file_header.timestamp << '\n';
    std::cout << "version:       " << file_header.version << '\n';
    std::cout << '\n';

    while(auto event = reader.next<EventBody>()) {
        std::cout << "orderId:       " << event->orderId << '\n';
        std::cout << "instrumentId:  " << event->instrumentId << '\n';
        std::cout << "quantity:      " << event->quantity << '\n';
        std::cout << "price:         " << event->price << '\n';
        std::cout << "side:          " << static_cast<int>(event->side) << '\n';
        std::cout << '\n';
    }

    reader.close();

    return EXIT_SUCCESS;
}
