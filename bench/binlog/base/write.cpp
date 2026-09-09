// bench/binlog/base/write.cpp

#include <benchmark/benchmark.h>

#include "../fixtures.hpp"
#include "../schema.hpp"

#include <fcntl.h>
#include <unistd.h>

using bench::schema::Event;

namespace {

const char* Path = "benchmark-write.bin";

// One syscall per event, so a smaller batch keeps the benchmark short.
constexpr std::size_t WriteBatch = 100'000;

} // namespace

// Baseline: unbuffered write() syscall per event. This is the floor for
// any logger that does not buffer in user space.
static void BM_Write(benchmark::State& state)
{
    const auto& events = bench::events();

    const int fd = ::open(Path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        state.SkipWithError("failed to open benchmark file");
        return;
    }

    for (auto _ : state)
    {
        ::lseek(fd, 0, SEEK_SET);

        for (std::size_t i = 0; i < WriteBatch; ++i)
        {
            const auto& event = events[i];

            benchmark::DoNotOptimize(&event);

            auto written = ::write(fd, &event, sizeof(Event));
            benchmark::DoNotOptimize(written);
        }

        benchmark::ClobberMemory();
    }

    ::close(fd);

    state.SetItemsProcessed(
        state.iterations() * static_cast<int64_t>(WriteBatch));

    state.SetBytesProcessed(
        state.iterations() *
        static_cast<int64_t>(WriteBatch * sizeof(Event)));
}

BENCHMARK(BM_Write);

BENCHMARK_MAIN();
