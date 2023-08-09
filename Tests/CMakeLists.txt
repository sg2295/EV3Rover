# add_library(ev3dev-dummy INTERFACE)
# target_include_directories(ev3dev-dummy INTERFACE ev3dev-dummy)

add_executable(example-test test.cpp)
target_include_directories(example-test PRIVATE include)
target_link_libraries(example-test PRIVATE report gtest_main)  # TODO: Add ev3dev-dummy
