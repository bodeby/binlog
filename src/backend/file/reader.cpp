// src/backend/file/reader.cpp

#include "binlog/backend/file/reader.hpp"

// STL
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace binlog::backend {

FileReader::FileReader(const std::filesystem::path& path) {
    constexpr auto mode = std::ios::binary | std::ios::in;
    file_.open(path, mode);
    if (!file_) throw std::runtime_error("could not open file!");
}

bool FileReader::read(void* buffer, std::size_t size) noexcept {
    if (!file_.is_open()) return false;
    file_.read(static_cast<char*>(buffer), static_cast<std::streamsize>(size));
    return file_.good();
}

void FileReader::close() {
    file_.close();
};

} // namespace binlog::backend
