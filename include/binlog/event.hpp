// include/binlog/event.hpp

#pragma once

#include <cstdint>

namespace binlog {

struct OrderAdded {
  std::uint64_t tsc;
  std::uint64_t px;
  std::uint64_t qty;
};

}; // namespace binlog
