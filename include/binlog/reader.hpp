// include/binlog/decoer.hpp

#pragma once

#include <utility>

namespace binlog {

template <typename Backend> class Reader {
  public:
    explicit Reader(Backend backend) : backend_(std::move(backend)) {}

    template <typename T> void read(const T& event) {
        backend_.read(&event, sizeof(event));
    }

    void flush() {
        backend_.flush();
    }

    void close() {
        backend_.close();
    }

  private:
    Backend backend_;
};

} // namespace binlog
