#include <iostream>

#include "observation.h"
#include "ev3dev.h"

#include "report.h"

using namespace observation;

int main() {
  Log("Starting observation test\n");
  USSensorWrapper us_sensor{ev3dev::OUTPUT_C, ev3dev::INPUT_1};
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
