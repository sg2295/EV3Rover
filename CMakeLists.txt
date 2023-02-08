cmake_minimum_required(VERSION 3.1.0)

# set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
# set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

set(CMAKE_CXX_STANDARD 11)  # TODO: Should we use 14/17/20?
# message("Compiling with c++${CMAKE_CXX_STANDARD}.")

# add_library(example-lib impl.cpp)

project(EV3_Test)
add_compile_options("-static")
add_executable(example-lib-run main.cpp)
target_link_libraries(example-lib-run PRIVATE "/usr/arm-linux-gnueabi/")
# target_link_libraries(example-lib-run PRIVATE /usr/arm-linux-gnueabi/)
# target_link_libraries(example-lib-run PRIVATE example-lib)


# Need to write in terminal:
# ` export QEMU_LD_PREFIX=/usr/arm-linux-gnueabi `
