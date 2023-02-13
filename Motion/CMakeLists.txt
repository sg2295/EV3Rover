add_library(motion motor.cpp)
target_include_directories(motion PUBLIC include)
target_link_libraries(motion PRIVATE ev3dev)
