add_library(observation observation.cpp)
target_include_directories(observation PUBLIC include)
target_link_libraries(observation PRIVATE ev3dev report)

add_executable(observation-test observation-test.cpp)
target_include_directories(observation-test PRIVATE include)
target_link_libraries(observation-test PRIVATE ev3dev observation)
# TODO: Fix Cmake to use report in observation-test target as well... Getting multiple definitions.
