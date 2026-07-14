// include/binlog/backend/file.cpp

#include "binlog/backend/file.hpp"

// STL
#include <ios>
#include <iostream>
#include <stdexcept>

namespace binlog::backend {

FileBackend::FileBackend(const std::filesystem::path& path) {
    file_.open(path, std::ios::binary | std::ios::trunc);

    if (!file_) {
        throw std::runtime_error("could not open file!");
    }
}

void FileBackend::write(const void* data, std::size_t size) noexcept {
    file_.write(static_cast<const char*>(data), static_cast<std::streamsize>(size));
    std::clog << "writing to file" << '\n';
}

void FileBackend::flush() {
    file_.flush();
    std::clog << "flushing file" << '\n';
};

void FileBackend::close() {
    file_.close();
    std::clog << "closing file" << '\n';
};

} // namespace binlog::backend
