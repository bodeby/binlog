// include/binlog/backend/file/reader.hpp

#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace binlog::backend {

class FileReader {
  public:
    explicit FileReader(const std::filesystem::path& path);

    void read(void* buffer, std::size_t size) noexcept;

    void flush();
    void close();

  private:
    std::fstream file_;
};

} // namespace binlog::backend
