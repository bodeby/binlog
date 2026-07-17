# ------------------------------------------------------------------
# GTEST SETUP
# ------------------------------------------------------------------

include(GoogleTest)

# ------------------------------------------------------------------
# CORE / CONCURRENCY
# ------------------------------------------------------------------

add_executable(binlog_unit_tests)

target_link_libraries(binlog_unit_tests
  PRIVATE GTest::gtest_main binlog
)

gtest_discover_tests(binlog_unit_tests)
