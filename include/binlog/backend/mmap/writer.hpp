// include/binlog/backend/mmap/writer.hpp

#pragma once

#include <cstddef>
#include <cstring>
#include <filesystem>
#include <stdexcept>
#include <system_error>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace binlog::backend {

constexpr std::size_t KB = 1024;
constexpr std::size_t MB = 1024 * KB;

class MemoryMappedWriter {
  public:
    explicit MemoryMappedWriter(const std::filesystem::path& path, std::size_t capacity = 256 * MB)
        : capacity_(capacity) {
        fd_ = ::open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (fd_ == -1)
            throw std::system_error(errno, std::generic_category(), "failed to open file");

        if (::ftruncate(fd_, static_cast<off_t>(capacity_)) == -1) {
            ::close(fd_);
            throw std::system_error(errno, std::generic_category(), "failed to resize file");
        }

        base_ = static_cast<std::byte*>(
            ::mmap(nullptr, capacity_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));

        if (base_ == MAP_FAILED) {
            ::close(fd_);
            throw std::system_error(errno, std::generic_category(), "failed to mmap file");
        }

        cursor_ = base_;
        end_ = base_ + capacity_;
    }

    ~MemoryMappedWriter() {
        close();
    }

    MemoryMappedWriter(const MemoryMappedWriter&) = delete;
    MemoryMappedWriter& operator=(const MemoryMappedWriter&) = delete;

    MemoryMappedWriter(MemoryMappedWriter&& other) noexcept
        : fd_(other.fd_)
        , capacity_(other.capacity_)
        , base_(other.base_)
        , cursor_(other.cursor_)
        , end_(other.end_)
    {
        other.fd_ = -1;
        other.capacity_ = 0;
        other.base_ = nullptr;
        other.cursor_ = nullptr;
        other.end_ = nullptr;
    }

    MemoryMappedWriter& operator=(MemoryMappedWriter&& other) noexcept
    {
        if (this == &other)
            return *this;

        close();

        fd_ = other.fd_;
        capacity_ = other.capacity_;
        base_ = other.base_;
        cursor_ = other.cursor_;
        end_ = other.end_;

        other.fd_ = -1;
        other.capacity_ = 0;
        other.base_ = nullptr;
        other.cursor_ = nullptr;
        other.end_ = nullptr;

        return *this;
    }

    void write(const void* buffer, std::size_t size) {
        if (cursor_ + size > end_)
            throw std::runtime_error("memory mapped file capacity exceeded");

        std::memcpy(cursor_, buffer, size);
        cursor_ += size;
    }

    void flush() {
        if (base_ == nullptr)
            return;

        if (::msync(base_, bytes_written(), MS_SYNC) == -1)
            throw std::system_error(errno, std::generic_category(), "msync failed");
    }

    void close() {
        if (fd_ == -1)
            return;

        const auto written = bytes_written();

        (void) ::msync(base_, written, MS_SYNC);
        (void) ::munmap(base_, capacity_);
        (void) ::ftruncate(fd_, static_cast<off_t>(written));
        (void) ::close(fd_);

        fd_ = -1;
        base_ = nullptr;
        cursor_ = nullptr;
        end_ = nullptr;
    }

  private:
    std::size_t bytes_written() const noexcept {
        return static_cast<std::size_t>(cursor_ - base_);
    }

  private:
    int fd_{-1};

    std::size_t capacity_{0};
    std::byte* base_{nullptr};
    std::byte* cursor_{nullptr};
    std::byte* end_{nullptr};
};

} // namespace binlog::backend
