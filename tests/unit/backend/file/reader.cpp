// tests/unit/backend/file/reader.hpp

#include <gtest/gtest.h>

// STL
#include <filesystem>

// unit-of-test
#include <binlog/backend/file/reader.hpp>

using namespace binlog::backend;

// ----------------- CASES -----------------

TEST(FileReader, Hello) {
    std::filesystem::path path("events.bin");
    binlog::backend::FileReader backend(path);
}
