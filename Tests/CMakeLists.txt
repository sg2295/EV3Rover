add_library(ev3dev INTERFACE)
target_include_directories(ev3dev INTERFACE ev3dev-dummy)

# TODO: Remove - unneeded; we'll do inline tests
add_executable(example-test test.cpp)
target_include_directories(example-test PRIVATE include)
target_link_libraries(example-test PRIVATE report gtest_main)
