// src/logger.cpp

#include "binlog/logger.hpp"

#include <iostream>

namespace binlog {

void Logger::log() { std::clog("hello world"); }

} // namespace binlog
