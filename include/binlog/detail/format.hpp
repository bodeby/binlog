// include/binlog/detail/format.hpp

#include "binlog/types/internal.hpp"
#include "binlog/types/time.hpp"

namespace binlog::detail {

struct FileHeader {
    time::CycleCount timestamp{};
    internal::Magic magic{};
    internal::FormatVersion version{};
    internal::FileFlags flags{};
};

static_assert(sizeof(FileHeader) == 16);

struct EventHeader {
    time::CycleCount timestamp{};
    internal::FormatVersion version{};
    internal::PayloadSize size{};
    internal::EventType eventType{};
};

static_assert(sizeof(EventHeader) == 16);

} // namespace binlog::detail
