add_library(hardware-scope INTERFACE)
target_include_directories(hardware-scope INTERFACE include-scope)

add_subdirectory(Motion)
add_subdirectory(Observation)

add_library(hardware hardware.cpp)
target_include_directories(hardware PUBLIC include)
target_link_libraries(hardware PRIVATE ev3dev report motion observation)  # TODO: Do we need the inc. scope here?

add_executable(hardware-test hardware-test.cpp)
target_include_directories(hardware-test PRIVATE include)
target_link_libraries(hardware-test PRIVATE ev3dev hardware report)
