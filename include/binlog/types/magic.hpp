// include/binlog/types/magic.hpp

#pragma once

#include "binlog/types/base.hpp"

#include <cstdint>

namespace binlog {

struct MagicTag;
using Magic = BaseType<std::uint32_t, MagicTag>;
static_assert(validateBaseType<Magic, std::uint32_t>());

} // namespace binlog
