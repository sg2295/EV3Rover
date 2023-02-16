add_library(observation STATIC observation.cpp)
target_include_directories(observation PUBLIC include)
target_link_libraries(observation PRIVATE ev3dev report hardware-scope)

add_executable(observation-test observation-test.cpp)
target_include_directories(observation-test PRIVATE include)
target_link_libraries(observation-test PRIVATE ev3dev observation report hardware-scope)
