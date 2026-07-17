// src/backend/mmap/reader.cpp

#include "binlog/backend/mmap/reader.hpp"

namespace binlog::backend {

MemoryMappedReader::MemoryMappedReader(const std::filesystem::path& path) {
    constexpr auto mode = std::ios::binary | std::ios::in;
    file_.open(path, mode);
    if (!file_) throw std::runtime_error("could not open file!");
};

void MemoryMappedReader::close() {};

void MemoryMappedReader::read(void* buffer, std::size_t size) noexcept {};

} // namespace binlog::backend
