#include <iostream>

#include "observation.h"
#include "ev3dev.h"

#include "report.h"

using namespace observation;

int main() {
  Log("Starting observation test\n");
  auto us_sensor = USSensorWrapper{ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  // while (true) {
  //   std::cout << "pos=" << us_sensor.motor->position() << std::endl;
  // }
  // Test static sensing...
  for (unsigned j = 0; j < 4; ++j) {
    auto sensor_readings = us_sensor.scan();
    for (auto i : sensor_readings)
      std::cout << '[' << i << "], ";
    std::cout << std::endl;
  }
  return 0;
}



// # TODO: add hardware-scope

// add_subdirectory(Motion)
// add_subdirectory(Observation)

// add_library(hardware hardware.cpp)
// target_include_directories(hardware PUBLIC include)
// target_link_libraries(hardware PRIVATE report motion observation)
