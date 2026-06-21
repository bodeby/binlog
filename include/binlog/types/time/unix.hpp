// include/binlog/time/unix.hpp

#pragma once

#include "binlog/types/base.hpp"

#include <cstdint>

namespace binlog::time {

struct UnixTag;
using UnixTime = BaseType<std::uint64_t, UnixTag>;
static_assert(validateBaseType<UnixTime, std::uint64_t>());

} // namespace binlog::time
