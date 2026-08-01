// include/binlog/backend/file/writer.hpp

#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace binlog::backend {

class FileWriter {
  public:
    explicit FileWriter(const std::filesystem::path& path) {
        constexpr auto mode = std::ios::binary | std::ios::out | std::ios::trunc;
        file_.open(path, mode);
        if (!file_) throw std::runtime_error("could not open file!");
    };

    void write(const void* buffer, std::size_t size) noexcept {
        file_.write(static_cast<const char*>(buffer), static_cast<std::streamsize>(size));
    };

    void flush() { file_.flush(); };
    void close() { file_.close(); };

  private:
    std::fstream file_;
};

} // namespace binlog::backend
