add_executable(file_writer_benchmark
    file/writer.cpp
)

target_link_libraries(file_writer_benchmark
    PRIVATE
        binlog
        benchmark::benchmark_main
)

add_executable(file_reader_benchmark
    file/reader.cpp
)

target_link_libraries(file_reader_benchmark
    PRIVATE
        binlog
        benchmark::benchmark_main
)
