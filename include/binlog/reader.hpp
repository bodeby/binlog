// include/binlog/reader.hpp

#pragma once

#include "binlog/types/internal.hpp"
#include "detail/format.hpp"

#include <iostream>
#include <optional>
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

    template <typename T>
    std::optional<T> next()
        requires(!std::same_as<T, detail::FileHeader>)
    {
        detail::EventHeader header{};

        if (!backend_.read(&header, sizeof(header)))
            return std::nullopt;

        std::cout << "version = "
                  << header.version << ", size = "
                  << header.size.raw() << '\n';

        if (header.version != internal::current_version)
            throw std::runtime_error("bad event version");

        return read<T>();
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
    template <typename T> T read() {
        T value{};
        backend_.read(&value, sizeof(T));
        return value;
    }

  private:
    Backend backend_;
    detail::FileHeader fileheader_;
};

} // namespace binlog
