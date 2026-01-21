find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests)
target_sources(tests PRIVATE math.cpp)
target_link_libraries(tests PRIVATE gtest::gtest)

gtest_discover_tests(tests)
