// apps/encode/src/schema.hpp

#pragma once

#include <cstdint>

namespace encode::schema {

enum class EventType : std::uint8_t {
    BookUpdate,
};

enum class Side : std::uint8_t {
    Buy,
    Sell,
};

// file setup

struct FileHeader {
    uint32_t magic;
    uint16_t version;
    uint16_t flags;
    uint64_t startTimestamp;
};

static_assert(sizeof(FileHeader) == 16);

struct EventHeader {
    std::uint64_t timestamp;
    std::uint32_t size;
    std::uint8_t version;
};

static_assert(sizeof(EventHeader) == 16);

struct EventBody {
    uint64_t orderId;
    uint32_t instrumentId;
    uint32_t quantity;
    double price;
    Side side;
};

static_assert(sizeof(EventBody) == 32);

} // namespace encode::schema
