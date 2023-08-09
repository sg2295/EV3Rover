cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 14)  # Cannot use 17 and above...
# message("Compiling with c++${CMAKE_CXX_STANDARD}.")

project(EV3Rover)

# Check that build type was provided. Otherwise default to Release.
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type not specified, using `Release`.")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose build type. (Default=Release)" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel")
endif ()

# Set up compiler flags for build type
message(STATUS "Building for ${CMAKE_BUILD_TYPE}.")
string(TOLOWER "${CMAKE_BUILD_TYPE}" build)
if (build STREQUAL "debug")  # As much debug, as pedantic as we possibly can
  add_compile_options(-O0 -g)
elseif (build STREQUAL "release")  # "Normal" build
  add_compile_options(-O3 -DNDEBUG)
elseif (build STREQUAL "minsizerel")  # Smallest possible executable
  add_compile_options(-Os -s -DNDEBUG)
endif ()


# Default compile options - not specific to build type...
add_compile_options(-static -Wall -Wextra -pedantic -Werror)

# Enable/disable logging
option(ENABLE_LOGGING "Enable logging and user error reporting. On by default." ON)
if (ENABLE_LOGGING)
  add_definitions(-DENABLE_LOGGING)  # We don't have access to add_compile_definitons...
endif ()

# Add compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                                                           ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)

# N.B. This project requires the ev3dev-lang-cpp library: https://github.com/ddemidov/ev3dev-lang-cpp.
find_package(ev3dev REQUIRED)

add_subdirectory(Report)
add_subdirectory(Hardware)

add_subdirectory(External/googletest)
add_subdirectory(Tests)

add_executable(ev3rover main.cpp)
target_link_libraries(ev3rover PRIVATE hardware-scope ev3dev hardware report)
