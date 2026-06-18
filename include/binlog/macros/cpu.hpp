// include/binlog/macros/cpu.hpp

#pragma once

#include <immintrin.h>

namespace binlog::macro {

#define BL_CPU_RELAX() _mm_pause()
#define BL_PREFETCH(addr) __builtin_prefetch(addr, 0, 3)
#define BL_TRAP() __builtin_trap()

} // namespace binlog::macro
