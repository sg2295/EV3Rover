add_library(motion STATIC motion.cpp)
target_include_directories(motion PUBLIC include)
target_link_libraries(motion PRIVATE ev3dev report hardware-scope)
