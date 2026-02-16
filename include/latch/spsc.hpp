// include/latch/spsc.hpp

#pragma once

/**
 * Purpose: Pass objects between threads (SPSC / MPSC)
 * Ownership: Usually the consumer owns the object after popping
 * Hot-Path Optim: Lock-free, cache-friendly queue
 * Use-case: MarketData → Strategy delivery
 */

#include <assert.h>
#include <atomic>  // thread-safe sequence counter
#include <cstddef> // for std::size_t (portable size type)
#include <vector>  // buffer for batch processing

namespace latch {

template <typename T> class SPSC {
public:
  explicit SPSC(std::size_t capacity)
      : capacity_(capacity), mask_(capacity - 1), buffer_(capacity) {
    // enforce power-of-two
    assert((capacity & mask_) == 0);
  }

  bool try_push(const T &item) {
    const std::size_t tail = tail_.load(std::memory_order_relaxed);
    const std::size_t next = (tail + 1) & mask_;

    if (next == head_.load(std::memory_order_acquire)) {
      return false; // full
    }

    buffer_[tail] = item;
    tail_.store(next, std::memory_order_release);
    return true;
  }

  bool try_pop(T &item) {
    const std::size_t head = head_.load(std::memory_order_relaxed);

    if (head == tail_.load(std::memory_order_acquire)) {
      return false; // empty
    }

    item = buffer_[head];
    head_.store((head + 1) & mask_, std::memory_order_release);
    return true;
  }

private:
  const std::size_t capacity_;
  const std::size_t mask_;
  std::vector<T> buffer_;

  alignas(64) std::atomic<std::size_t> head_{0}; // consumer-owned
  alignas(64) std::atomic<std::size_t> tail_{0}; // producer-owned
};

} // namespace latch
