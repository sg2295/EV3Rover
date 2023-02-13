cmake_minimum_required(VERSION 3.1.0)

# set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
# set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

set(CMAKE_CXX_STANDARD 14)  # TODO: Should we use 14/17/20?
# message("Compiling with c++${CMAKE_CXX_STANDARD}.")

# add_library(example-lib impl.cpp)

project(EV3_SLAM)
add_compile_options("-static")

# TODO: This project requires the ev3dev-lang-cpp library: https://github.com/ddemidov/ev3dev-lang-cpp.
add_library(ev3dev ev3dev-lang-cpp/ev3dev.cpp)
target_include_directories(ev3dev PUBLIC ev3dev-lang-cpp/)

add_subdirectory(Motion)

add_executable(ev3slam main.cpp)
target_link_libraries(ev3slam PRIVATE "/usr/arm-linux-gnueabi/" ev3dev motion)
# TODO: Can remove /usr/arm...

# add_executable(example-lib-run main.cpp)
# target_link_libraries(example-lib-run PRIVATE "/usr/arm-linux-gnueabi/" ev3dev)


# target_link_libraries(example-lib-run PRIVATE /usr/arm-linux-gnueabi/)
# target_link_libraries(example-lib-run PRIVATE example-lib)


# Need to write in terminal:
# ` export QEMU_LD_PREFIX=/usr/arm-linux-gnueabi `

# How to build EV3DEV cpp lang lib (TODO: Add to Dockerfile)
#   mkdir build
#   cd build
#   cmake .. -DEV3DEV_PLATFORM=EV3
#   make
