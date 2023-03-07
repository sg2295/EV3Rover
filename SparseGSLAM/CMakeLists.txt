add_subdirectory(LSE)

add_library(sparse-gslam STATIC main.cpp)
target_include_directories(sparse-gslam PUBLIC include)
target_link_libraries(sparse-gslam PRIVATE hardware-scope hardware report)

# add_executable(sparse-gslam-test hardware-test.cpp)
# target_include_directories(sparse-gslam-test PRIVATE include)
# target_link_libraries(sparse-gslam-test PRIVATE hardware report)
