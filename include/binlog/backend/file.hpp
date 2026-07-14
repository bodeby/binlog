// include/binlog/backend/mmap.hpp

#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace binlog::backend {

class FileBackend {
  public:
    explicit FileBackend(const std::filesystem::path& path);

    void write(const void* data, std::size_t size) noexcept;
    void flush();
    void close();

  private:
    std::ofstream file_;
};

} // namespace binlog::backend
