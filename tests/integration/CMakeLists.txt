# ------------------------------------------------------------------
# GTEST SETUP
# ------------------------------------------------------------------

include(GoogleTest)

# ------------------------------------------------------------------
# CORE / CONCURRENCY
# ------------------------------------------------------------------

add_executable(binlog_integration_tests
  round_trip.cpp
)

target_link_libraries(binlog_integration_tests
  PRIVATE GTest::gtest_main binlog
)

gtest_discover_tests(binlog_integration_tests)
