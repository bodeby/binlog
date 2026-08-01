# ------------------------
# Baseline Benchmarks
# ------------------------

add_executable(fwrite_buffered_benchmark
    base/fwrite_buffered.cpp
)

target_link_libraries(fwrite_buffered_benchmark
    PRIVATE
        benchmark::benchmark_main
)

add_executable(fwrite_flush_benchmark
    base/fwrite_flush.cpp
)

target_link_libraries(fwrite_flush_benchmark
    PRIVATE
        benchmark::benchmark_main
)

# ------------------------
# FileWriter Benchmarks
# ------------------------

add_executable(file_reader_benchmark
    file/reader.cpp
)

target_link_libraries(file_reader_benchmark
    PRIVATE
        binlog
        benchmark::benchmark_main
)

add_executable(file_writer_benchmark
    file/writer.cpp
)

target_link_libraries(file_writer_benchmark
    PRIVATE
        binlog
        benchmark::benchmark_main
)

# ------------------------
# MMAP Benchmarks
# ------------------------

add_executable(mmap_writer_benchmark
    mmap/writer.cpp
)

target_link_libraries(mmap_writer_benchmark
    PRIVATE
        binlog
        benchmark::benchmark_main
)
