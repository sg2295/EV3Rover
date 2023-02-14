#include <iostream>

#include "report.h"

#include "observation.h"
#include "ev3dev.h"

using namespace observation;

int main() {
  Log("Starting observation test\n");
  auto us_sensor = USSensorWrapper{ev3dev::OUTPUT_D, ev3dev::INPUT_1};
  // TODO: Test multiscan later on...
  while (true) {
    Log("Reading: ", us_sensor.scan(), ".\n");
  }
  return 0;
}
