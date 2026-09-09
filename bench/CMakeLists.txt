# benchmarks/CMakeLists.txt

# ------------------------------------------------------------------
# Google Benchmark Framework
# ------------------------------------------------------------------
#
# CodSpeed's fork of Google Benchmark is used instead of the upstream
# repository. It is a drop-in replacement: without -DCODSPEED_MODE it
# behaves exactly like upstream Google Benchmark, and with
# -DCODSPEED_MODE=simulation the benchmarks become instrumentable by
# CodSpeed. See https://codspeed.io/docs/benchmarks/cpp

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-cpp.git
  GIT_TAG v2.4.0
  SOURCE_SUBDIR google_benchmark
)

# Disable benchmark's own tests (important)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)

# ------------------------------------------------------------------
# Discover subdirectories
# ------------------------------------------------------------------

add_subdirectory(binlog)
