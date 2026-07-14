// include/binlog/backend/mmap.hpp

#pragma once

#include <cstddef>
#include <string>

namespace binlog::backends {

class MMAP {
  public:
    explicit MMAP(std::string path) : path_(std::move(path)) {};

    void write(const void* data, std::size_t size) noexcept;

  private:
    std::string path_;
};

} // namespace binlog::backends
