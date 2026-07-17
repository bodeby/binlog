// include/binlog/reader.hpp

#pragma once

#include "detail/format.hpp"

#include <stdexcept>
#include <utility>


namespace binlog {

template <typename Backend> class Reader {
  public:
    explicit Reader(Backend backend) : backend_(std::move(backend)) {
        auto file_header = read<detail::FileHeader>();

        if (file_header.magic != internal::file_magic)
            throw std::runtime_error("bad magic ");

        if (file_header.version != internal::current_version)
            throw std::runtime_error("bad version");

        fileheader_ = file_header; // assign
    }

    template <typename T> T read() {
        T value{};
        backend_.read(&value, sizeof(T));
        return value;
    }

    void flush() {
        backend_.flush();
    }

    void close() {
        backend_.close();
    }

    const detail::FileHeader& fileheader() const noexcept {
        return fileheader_;
    }

  private:
    Backend backend_;
    detail::FileHeader fileheader_;
};

} // namespace binlog
