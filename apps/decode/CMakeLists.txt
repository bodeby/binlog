add_executable(binlog-decode
    src/main.cpp
)

target_link_libraries(binlog-decode
    PRIVATE
        binlog
)
