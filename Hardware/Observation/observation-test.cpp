#include <iostream>

#include "observation.h"
#include "ev3dev.h"

#include "report.h"

using namespace observation;

int main() {
  Log("Starting observation test\n");
  USSensorWrapper us_sensor{ev3dev::OUTPUT_C, ev3dev::INPUT_1};

  auto sensor_readings = us_sensor.scan();
  for (auto const& bearing : sensor_readings) {
      for (auto const reading : bearing)
        std::cout << '[' << reading << "], ";
    std::cout << std::endl;
  }
  return 0;
}
