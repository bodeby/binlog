// include/binlog/detail/format.hpp

#include <cstdint>

namespace binlog::detail {

struct FileHeader {
    uint32_t magic;
    uint16_t version;
    uint16_t flags;
    uint64_t timestamp;
};

static_assert(sizeof(FileHeader) == 16);

struct EventHeader {
    std::uint64_t timestamp;
    std::uint32_t size;
    std::uint8_t version;
};

static_assert(sizeof(EventHeader) == 16);

} // namespace binlog::detail
