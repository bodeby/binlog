// include/binlog/backend/file/reader.hpp

#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace binlog::backend {

class FileReader {
  public:
    explicit FileReader(const std::filesystem::path& path) {
        constexpr auto mode = std::ios::binary | std::ios::in;
        file_.open(path, mode);
        if (!file_) throw std::runtime_error("could not open file!");
    };

    bool read(void* buffer, std::size_t size) noexcept {
        if (!file_.is_open()) return false;
        file_.read(static_cast<char*>(buffer), static_cast<std::streamsize>(size));
        return file_.good();
    };

    void next(void* buffer, std::size_t size) noexcept {

    };

    void close() { file_.close(); };

  private:
    std::fstream file_;
};

} // namespace binlog::backend
