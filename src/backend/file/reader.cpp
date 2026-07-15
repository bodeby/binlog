// src/backend/file/reader.cpp

#include "binlog/backend/file/reader.hpp"

// STL
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace binlog::backend {

FileReader::FileReader(const std::filesystem::path& path) {
    constexpr auto mode = std::ios::binary | std::ios::out | std::ios::trunc;
    file_.open(path, mode);

    if (!file_) {
        throw std::runtime_error("could not open file!");
    }
}

void FileReader::read(void* buffer, std::size_t size) noexcept {
    std::clog << "reading file" << '\n';

    if (!file_.is_open())
        return;

    const auto buf = file_.rdbuf();

    // snextc : Advance to next position and get character (public member function)
    // sbumpc : Get current character and advance to next position (public member function)
    // sgetc  : Get current character (public member function)
    // sgetn  : Get sequence of characters (public member function)
}

void FileReader::flush() {
    file_.flush();
};

void FileReader::close() {
    file_.close();
};

} // namespace binlog::backend
