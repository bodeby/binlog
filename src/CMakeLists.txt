add_library(binlog)

target_sources(binlog
    PRIVATE
    backend/file/reader.cpp
    backend/file/writer.cpp

    backend/mmap/reader.cpp
    backend/mmap/writer.cpp
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
