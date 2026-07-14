// include/binlog/logger.hpp

#pragma once

#include <utility>

namespace binlog {

template <typename Backend> class Logger {
  public:
    explicit Logger(Backend backend) : backend_(std::move(backend)) {}

    template <typename T> void write(const T& event) {
        backend_.write(&event, sizeof(event));
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
