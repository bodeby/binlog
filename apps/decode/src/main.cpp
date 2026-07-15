// apps/decode/src/main.cpp

#include "schema.hpp"

// STL
#include <cstdlib>
#include <filesystem>

// library
#include <binlog/backend/file/reader.hpp>
#include <binlog/reader.hpp>

using decode::schema::EventHeader;
using decode::schema::EventBody;

int main() {

    std::filesystem::path path("events.bin");
    binlog::backend::FileReader backend(path);

    binlog::Reader reader(std::move(backend));

    auto header = reader.read<EventHeader>();
    auto body = reader.read<EventBody>();

    reader.flush();
    reader.close();

    return EXIT_SUCCESS;
}
