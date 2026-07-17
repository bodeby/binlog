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

    // ------ ARRANGE ------

    TempFile file(path);

    detail::FileHeader expected{
        .timestamp = time::CycleCount{0},
        .magic = internal::file_magic,
        .version = internal::current_version,
        .flags = internal::FileFlags{},
    };

    auto body = Body{};

    {
        backend::FileWriter backend(file.path());
        Writer writer(std::move(backend));
        writer.write(body);
    }

    // ------ ACT ------

    backend::FileReader backend(file.path());
    Reader reader(std::move(backend));
    auto actual = reader.fileheader();

    // ------ ASSERT ------

    EXPECT_EQ(expected.timestamp, actual.timestamp);
    EXPECT_EQ(expected.magic, actual.magic);
    EXPECT_EQ(expected.version, actual.version);
    EXPECT_EQ(expected.flags, actual.flags);

    // ------ CLEAN ------

    std::filesystem::remove(path);
}

TEST(RoundTrip, ReadsEventHeader) {

    // ------ ARRANGE ------

    TempFile file(path);

    auto body = Body{};

    auto expected = detail::EventHeader{
        .timestamp = time::CycleCount{0},
        .version = internal::current_version,
        .size = internal::PayloadSize{sizeof(body)},
        .eventType = internal::EventType{0},
    };

    {
        backend::FileWriter backend(file.path());
        Writer writer(std::move(backend));
        writer.write(body);
    }

    // ------ ACT ------

    backend::FileReader backend(file.path());
    Reader reader(std::move(backend));
    auto actual = reader.read<detail::EventHeader>();

    // ------ ASSERT ------

    EXPECT_EQ(expected.timestamp, actual.timestamp);
    EXPECT_EQ(expected.version, actual.version);
    EXPECT_EQ(expected.size, actual.size);
    EXPECT_EQ(expected.eventType, actual.eventType);
};

TEST(RoundTrip, ReadsEventBody) {

    // ------ ARRANGE ------

    TempFile file(path);

    auto expected = Body{};
    auto header = detail::EventHeader{};

    {
        backend::FileWriter backend(file.path());
        Writer writer(std::move(backend));
        writer.write(expected);
    }

    // ------ ACT ------

    backend::FileReader backend(file.path());
    Reader reader(std::move(backend));

    auto event_header = reader.read<detail::EventHeader>();
    auto actual = reader.read<Body>();
    reader.close();

    // ------ ASSERT ------

    EXPECT_EQ(event_header.size.raw(), sizeof(expected));
    EXPECT_EQ(event_header.version, internal::current_version);
    EXPECT_EQ(event_header.timestamp, time::CycleCount{0});
    EXPECT_EQ(event_header.eventType, internal::EventType{0});

    EXPECT_EQ(expected.px, actual.px);
    EXPECT_EQ(expected.qty, actual.qty);
    EXPECT_EQ(expected.side, actual.side);
};

TEST(RoundTrip, DoubleRead) {

    // ------ ARRANGE ------

    TempFile file(path);

    auto expected = Body{};
    auto header = detail::EventHeader{};

    {
        backend::FileWriter backend(file.path());
        Writer writer(std::move(backend));
        writer.write(expected);
    }

    // ------ ACT ------

    backend::FileReader backend(file.path());
    Reader reader(std::move(backend));

    auto event_header = reader.read<detail::EventHeader>();
    auto actual = reader.read<Body>();
    auto acutal_2 = reader.read<Body>();
    auto acutal_3 = reader.read<Body>();
    reader.close();

    // ------ ASSERT ------

    EXPECT_EQ(expected.px, actual.px);
    EXPECT_EQ(expected.qty, actual.qty);
    EXPECT_EQ(expected.side, actual.side);

};
