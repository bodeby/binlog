cmake_minimum_required(VERSION 3.20)

project(
    binlog
    VERSION 0.1.0
    LANGUAGES CXX
)

add_library(binlog INTERFACE)

target_include_directories(binlog
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(binlog INTERFACE cxx_std_20)

option(BINLOG_BUILD_APPS "Build apps" ON)
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
