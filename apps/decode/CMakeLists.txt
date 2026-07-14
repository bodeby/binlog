add_executable(binlog-decode
    main.cpp
    decoder.cpp
)

target_link_libraries(binlog-decode
    PRIVATE
        binlog
)
