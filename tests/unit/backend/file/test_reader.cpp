// tests/unit/backend/file/reader.hpp

#include "binlog/types/internal.hpp"
#include "binlog/writer.hpp"
#include <gtest/gtest.h>

// STL
#include <filesystem>

// unit-of-test
#include <binlog/backend/file/reader.hpp>
#include <binlog/reader.hpp>

using namespace binlog::backend;

using binlog::detail::FileHeader;
using binlog::internal::Magic;

// ----------------- CASES -----------------

TEST(FileReader, Hello) {
    std::filesystem::path path("./events.bin");
    binlog::backend::FileReader backend(path);

    binlog::Reader reader(std::move(backend));
    auto header = reader.read<FileHeader>();

    EXPECT_EQ(header.magic, binlog::internal::file_magic);
}
