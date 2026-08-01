add_executable(write_file_benchmark
    write_file.cpp
)

target_link_libraries(write_file_benchmark
    PRIVATE
        binlog
        benchmark::benchmark_main
)
