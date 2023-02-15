
# TODO: Add hardware-scope library

add_subdirectory(Motion)
add_subdirectory(Observation)

add_library(hardware hardware.cpp)
target_include_directories(hardware PUBLIC include)
target_link_libraries(hardware PRIVATE ev3dev report motion observation)

# add_executable(hardware-test hardware-test.cpp)
# target_include_directories(hardware-test PRIVATE include)
# target_link_libraries(hardware-test PRIVATE ev3dev hardware report)
