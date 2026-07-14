add_library(binlog)

target_sources(binlog
    PRIVATE
    backend/mmap.cpp
)

target_include_directories(binlog
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(binlog
    PUBLIC
        cxx_std_20
)

add_library(binlog::binlog ALIAS binlog)
