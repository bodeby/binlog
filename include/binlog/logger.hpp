// include/binlog/logger.hpp

#pragma once

#include <string_view>

namespace binlog {

class Logger {
public:
  Logger() = default;
  ~Logger() = default;

  void log();

private:
  std::string_view path;
};

} // namespace binlog
