// src/backend/mmap/writer.cpp

#include "binlog/backend/mmap/writer.hpp"

namespace binlog::backend {

MemoryMappedWriter::MemoryMappedWriter(const std::filesystem::path& path) {};

void MemoryMappedWriter::close() {};

void MemoryMappedWriter::flush() {};

void MemoryMappedWriter::write(const void* buffer, std::size_t size) noexcept {};

} // namespace binlog::backend
