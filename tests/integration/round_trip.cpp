// tests/integration/round_trip.cpp

#include <gtest/gtest.h>

// STL
#include <cstdint>
#include <filesystem>
#include <utility>

// unit-of-test
#include <binlog/backend/file/reader.hpp>
#include <binlog/backend/file/writer.hpp>
#include <binlog/reader.hpp>
#include <binlog/types/internal.hpp>
#include <binlog/types/time/cycles.hpp>
#include <binlog/writer.hpp>

using namespace binlog;

class TempFile {
  public:
    explicit TempFile(std::filesystem::path path) : path_(std::move(path)) {}

    ~TempFile() {
        std::error_code ec;
        std::filesystem::remove(path_, ec);
    }

    TempFile(const TempFile& other) = delete;
    TempFile& operator=(const TempFile& other) = delete;

    TempFile(const TempFile&& other) = delete;
    TempFile&& operator=(const TempFile&& other) = delete;

    const std::filesystem::path& path() const {
        return path_;
    }

  private:
    std::filesystem::path path_;
};

const auto path = std::filesystem::temp_directory_path() / "binlog-roundtrip.bin";

struct Body {
    std::uint64_t px = 10;
    std::uint64_t qty = 15;
    bool side = true;
};

// ----------------- CASES -----------------

TEST(RoundTrip, ReadsFileHeader) {

    // arrange

    TempFile file(path);

    {
        backend::FileWriter backend(file.path());
        Writer writer(std::move(backend));
        writer.write(Body{});
    }

    // act

    backend::FileReader backend(file.path());
    Reader reader(std::move(backend));

    const auto& header = reader.fileheader();

    // assert

    EXPECT_EQ(header.magic, internal::file_magic);
    EXPECT_EQ(header.version, internal::current_version);
    EXPECT_EQ(header.timestamp, time::CycleCount{0});
}
