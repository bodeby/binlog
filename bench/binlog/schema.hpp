// bench/binlog/schema.hpp

#pragma once

#include <cstdint>

namespace bench::schema {

enum class Side : std::uint8_t {
    Buy,
    Sell,
};

struct Event {
    std::uint64_t orderId;
    std::uint32_t instrumentId;
    std::uint32_t quantity;
    double price;
    Side side;
};

static_assert(sizeof(Event) == 32);

} // namespace bench::schema
