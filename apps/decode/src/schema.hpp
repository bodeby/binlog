// apps/decode/src/schema.hpp

#pragma once

#include <cstdint>

namespace decode::schema {

enum class Side : std::uint8_t {
    Buy,
    Sell,
};

struct EventBody {
    uint64_t orderId;
    uint32_t instrumentId;
    uint32_t quantity;
    double price;
    Side side;
};

static_assert(sizeof(EventBody) == 32);

} // namespace decode::schema
