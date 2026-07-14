// include/binlog/logger.hpp

#pragma once

#include "binlog/concepts.hpp"

#include <utility>

namespace binlog {

template <Record Schema, typename Backend>
class Logger {
  public:
    explicit Logger(Backend backend) : backend_(std::move(backend)) {}

    void log(const Schema& record) {
        backend_.write(&record, sizeof(Schema));
    }

  private:
    Backend backend_;
};

} // namespace binlog
