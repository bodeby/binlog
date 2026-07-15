// include/binlog/types/internal.hpp

#pragma once

#include "binlog/types/base.hpp"

#include <cstdint>

namespace binlog::internal {

struct MagicTag;
using Magic = BaseType<std::uint32_t, MagicTag>;
static_assert(validateBaseType<Magic, std::uint32_t>());

struct FormatVersionTag;
using FormatVersion = BaseType<std::uint16_t, FormatVersionTag>;
static_assert(validateBaseType<FormatVersion, std::uint16_t>());

struct FileFlagsTag;
using FileFlags = BaseType<std::uint16_t, FileFlagsTag>;
static_assert(validateBaseType<FileFlags, std::uint16_t>());

struct PayloadSizeTag;
using PayloadSize = BaseType<std::uint16_t, PayloadSizeTag>;
static_assert(validateBaseType<PayloadSize, std::uint16_t>());

struct EventTypeTag;
using EventType = BaseType<std::uint8_t, EventTypeTag>;
static_assert(validateBaseType<EventType, std::uint8_t>());

// defaults

inline constexpr Magic file_magic{0x424C4F47};

inline constexpr FormatVersion current_version{1};

} // namespace binlog::internal
