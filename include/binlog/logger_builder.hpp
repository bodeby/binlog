// include/binlog/logger_builder.hpp

#pragma once

#include "binlog/logger.hpp"

namespace binlog {

template <Record Schema> class LoggerBuilder {
  public:
    template <typename Backend> auto backend(Backend backend) {
        return Logger<Schema, Backend>{std::move(backend)};
    }
};

} // namespace binlog
