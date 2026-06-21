// include/binlog/time/mono.hpp

#pragma once

#include "binlog/types/base.hpp"

#include <cstdint>

namespace binlog::time {

struct MonotonicTag;
using MonotonicTime = BaseType<std::uint64_t, MonotonicTag>;
static_assert(validateBaseType<MonotonicTime, std::uint64_t>());

} // namespace binlog::time
