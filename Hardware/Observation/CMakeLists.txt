add_library(observation STATIC observation.cpp)
target_include_directories(observation PUBLIC include)
target_link_libraries(observation PRIVATE ev3dev report hardware-scope)

add_executable(run-observation-test observation-test.cpp)
target_link_libraries(run-observation-test PRIVATE ev3dev observation report hardware-scope gtest_main)
