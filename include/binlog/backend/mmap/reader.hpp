// include/binlog/backend/mmap/reader.hpp

#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace binlog::backend {

class MemoryMappedReader {
  public:
    explicit MemoryMappedReader(const std::filesystem::path& path);

    void read(void* buffer, std::size_t size) noexcept;
    void close();

  private:
    std::fstream file_;
};

} // namespace binlog::backend
