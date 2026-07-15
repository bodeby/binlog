cmake_minimum_required(VERSION 3.20)

project(
    binlog
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

option(BINLOG_BUILD_APPS  "Build apps"  ON)

if(BINLOG_BUILD_APPS)
  add_subdirectory(apps)
endif()

# ------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------

option(BINLOG_BUILD_TESTS "Build tests" OFF)

if(BINLOG_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ------------------------------------------------------------------
# Benchmarks
# ------------------------------------------------------------------

option(BINLOG_BUILD_BENCH "Build bench" OFF)

if(BINLOG_BUILD_BENCH)
  add_subdirectory(bench)
endif()
