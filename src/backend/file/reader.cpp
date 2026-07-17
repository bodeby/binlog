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

    if (!file_) {
        throw std::runtime_error("could not open file!");
    }
}

void FileReader::read(void* buffer, std::size_t size) noexcept {

    if (!file_.is_open())
        return;

    std::clog << "before: " << file_.tellg() << " reading " << size << " bytes\n";
    file_.read(static_cast<char*>(buffer), static_cast<std::streamsize>(size));
    std::clog << "after : " << file_.tellg() << '\n';

    if (!file_)
        std::clog << "read failed\n"
                  << "  eof  = " << file_.eof() << '\n'
                  << "  fail = " << file_.fail() << '\n'
                  << "  bad  = " << file_.bad() << '\n'
                  << "  gcount = " << file_.gcount() << '\n';

    // snextc : Advance to next position and get character (public member function)
    // sbumpc : Get current character and advance to next position (public member function)
    // sgetc  : Get current character (public member function)
    // sgetn  : Get sequence of characters (public member function)
}

void FileReader::close() {
    file_.close();
};

} // namespace binlog::backend
