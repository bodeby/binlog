// include/binlog/backend/mmap.hpp

#include "binlog/backend/mmap.hpp"

// STL
#include <cstddef>
#include <iostream>

namespace binlog::backends {

void MMAP::write(const void* data, std::size_t size) noexcept {
    std::clog << "writing to mmap" << '\n';
}

} // namespace binlog::backends
