// include/binlog/writer.hpp

#pragma once

#include <utility>

// details
#include "binlog/detail/format.hpp"

// types
#include "binlog/types/internal.hpp"
#include "binlog/types/time/cycles.hpp"

namespace binlog {

template <typename Backend> class Writer {
  public:
    explicit Writer(Backend backend) : backend_(std::move(backend)) {
        detail::FileHeader header{
            .timestamp = time::CycleCount{0},
            .magic = internal::file_magic,
            .version = internal::current_version,
            .flags = internal::FileFlags{0},
        };

        backend_.write(&header, sizeof(header));
    }

    template <typename T> void write(const T& event) {
        detail::EventHeader header{
            .timestamp = time::CycleCount{0},
            .version = internal::current_version,
            .size = internal::PayloadSize{sizeof(event)},
        };

        backend_.write(&header, sizeof(header));
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
