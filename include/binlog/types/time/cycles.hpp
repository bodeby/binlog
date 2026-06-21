// include/binlog/time/cycles.hpp

#pragma once

#include "binlog/types/base.hpp"

#include <cstdint>

namespace binlog::time {

struct CycleCountTag;
using CycleCount = BaseType<std::uint64_t, CycleCountTag>;
static_assert(validateBaseType<CycleCount, std::uint64_t>());

} // namespace binlog::time
