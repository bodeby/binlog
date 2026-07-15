// src/backend/file/writer.cpp

#include "binlog/backend/file/writer.hpp"

// STL
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace binlog::backend {

FileWriter::FileWriter(const std::filesystem::path& path) {
    constexpr auto mode = std::ios::binary | std::ios::out | std::ios::trunc;
    file_.open(path, mode);

    if (!file_) {
        throw std::runtime_error("could not open file!");
    }
}

void FileWriter::write(const void* buffer, std::size_t size) noexcept {
    file_.write(static_cast<const char*>(buffer), static_cast<std::streamsize>(size));
    std::clog << "writing to file" << '\n';
}

void FileWriter::flush() {
    file_.flush();
};

void FileWriter::close() {
    file_.close();
};

} // namespace binlog::backend
