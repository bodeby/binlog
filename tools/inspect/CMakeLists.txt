add_executable(binlog-inspect
    main.cpp
)

target_link_libraries(binlog-inspect
    PRIVATE
        binlog
)
