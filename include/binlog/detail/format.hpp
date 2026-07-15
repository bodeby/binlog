// include/binlog/detail/format.hpp

#include "binlog/types/magic.hpp"
#include "binlog/types/time.hpp"
#include "binlog/types/time/cycles.hpp"

#include <cstdint>

namespace binlog::detail {

struct FileHeader {
    time::CycleCount timestamp;
    Magic magic;
    uint16_t version;
    uint16_t flags;
};

static_assert(sizeof(FileHeader) == 16);

struct EventHeader {
    time::CycleCount timestamp;
    std::uint32_t size;
    std::uint8_t version;
};

static_assert(sizeof(EventHeader) == 16);

} // namespace binlog::detail
