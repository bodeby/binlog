// include/binlog/backend/file/writer.hpp

#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace binlog::backend {

class FileWriter {
  public:
    explicit FileWriter(const std::filesystem::path& path);

    void write(const void* buffer, std::size_t size) noexcept;

    void flush();
    void close();

  private:
    std::fstream file_;
};

} // namespace binlog::backend
