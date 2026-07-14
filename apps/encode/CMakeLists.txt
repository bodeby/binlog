add_executable(binlog-encode
    src/main.cpp
)

target_link_libraries(binlog-encode
    PRIVATE
        binlog
)
