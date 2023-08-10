add_library(motion STATIC motion.cpp)
target_include_directories(motion PUBLIC include)
target_link_libraries(motion PRIVATE ev3dev report hardware-scope)

add_executable(motion-test motion-test.cpp)
target_link_libraries(motion-test PRIVATE report motion hardware-scope gtest_main)
