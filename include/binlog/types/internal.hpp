// include/binlog/types/internal.hpp

#pragma once

#include "binlog/types/base.hpp"

#include <cstdint>

namespace binlog::internal {

struct MagicTag;
using Magic = BaseType<std::uint32_t, MagicTag>;
static_assert(validateBaseType<Magic, std::uint32_t>());

std::ostream& operator<<(std::ostream& os, internal::Magic magic) {
    const auto value = static_cast<std::uint32_t>(magic.raw());

    os << static_cast<char>((value) & 0xff) << static_cast<char>((value >> 8) & 0xff)
       << static_cast<char>((value >> 16) & 0xff) << static_cast<char>((value >> 24) & 0xff);

    return os;
}

// ---

struct FormatVersionTag;
using FormatVersion = BaseType<std::uint16_t, FormatVersionTag>;
static_assert(validateBaseType<FormatVersion, std::uint16_t>());

// ---

struct FileFlagsTag;
using FileFlags = BaseType<std::uint16_t, FileFlagsTag>;
static_assert(validateBaseType<FileFlags, std::uint16_t>());

// ---

struct PayloadSizeTag;
using PayloadSize = BaseType<std::uint16_t, PayloadSizeTag>;
static_assert(validateBaseType<PayloadSize, std::uint16_t>());

// ---

struct EventTypeTag;
using EventType = BaseType<std::uint8_t, EventTypeTag>;
static_assert(validateBaseType<EventType, std::uint8_t>());

// defaults

constexpr std::uint32_t make_magic(const char (&s)[5]) {
    return static_cast<std::uint32_t>(s[0])
        | (static_cast<std::uint32_t>(s[1]) << 8)
        | (static_cast<std::uint32_t>(s[2]) << 16)
        | (static_cast<std::uint32_t>(s[3]) << 24);
}

inline constexpr Magic file_magic{make_magic("BNLG")};

inline constexpr FormatVersion current_version{1};

} // namespace binlog::internal
