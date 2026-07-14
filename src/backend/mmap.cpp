// include/binlog/backend/mmap.cpp

#include "binlog/backend/mmap.hpp"

// STL
#include <cstddef>
#include <iostream>

namespace binlog::backend {

void MemoryMappedFile::write(const void* data, std::size_t size) noexcept {
    std::clog << "writing to mmap" << '\n';
}

void MemoryMappedFile::flush() {
    std::clog << "flushing mmap file" << '\n';
};

void MemoryMappedFile::close() {
    std::clog << "closing mmap file" << '\n';
};

} // namespace binlog::backend
