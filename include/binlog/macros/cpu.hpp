// include/binlog/macros/cpu.hpp

#pragma once

#include <emmintrin.h>
#include <immintrin.h>

namespace binlog::cpu {

inline void relax() noexcept {
    _mm_pause();
};

template <typename T>
inline void prefetch(const T* addr) noexcept {
    __builtin_prefetch(addr, 0, 3);
};

[[noreturn]]
inline void trap() noexcept {
    __builtin_trap();
}

} // namespace binlog::cpu
