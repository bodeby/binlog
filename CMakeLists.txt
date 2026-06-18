cmake_minimum_required(VERSION 3.20)

project(
    binlog
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BINLOG_BUILD_TESTS ON)
option(BINLOG_BUILD_TOOLS ON)
option(BINLOG_BUILD_BENCHMARKS OFF)

add_subdirectory(src)

if(BINLOG_BUILD_TOOLS)
  add_subdirectory(tools)
endif()

if(BINLOG_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(BINLOG_BUILD_BENCHMARKS)
  add_subdirectory(bench)
endif()
