add_library(hardware-scope INTERFACE)
target_include_directories(hardware-scope INTERFACE include-scope)

add_subdirectory(Motion)
add_subdirectory(Observation)

add_library(hardware STATIC hardware.cpp)
target_include_directories(hardware PUBLIC include)
target_link_libraries(hardware PRIVATE hardware-scope ev3dev report motion observation)
