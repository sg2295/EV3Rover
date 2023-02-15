add_library(motion motion.cpp)
target_include_directories(motion PUBLIC include)
target_link_libraries(motion PRIVATE ev3dev report)
