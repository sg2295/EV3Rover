#include <iostream>

#include "observation.h"
#include "ev3dev.h"

using namespace observation;

int main() {
  std::cout << "Starting observation test\n";
  auto us_sensor = USSensorWrapper{ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  // while (true) {
  //   std::cout << "pos=" << us_sensor.motor->position() << std::endl;
  // }
  // Test static sensing...
  auto sensor_readings = us_sensor.scan();
  for (auto i : sensor_readings)
    std::cout << i << ", ";
  std::cout << std::endl;
  int x = 0;
  std::cin >> x;
  std::cout << std::endl;
  sensor_readings = us_sensor.scan();
  for (auto i : sensor_readings)
    std::cout << i << ", ";
  std::cout << std::endl;
  return 0;
}
