#include <iostream>

#include "ev3dev.h"
#include "motor.h"

using namespace motion;

int main() {
  // Main control loop here
  auto motors = MotorsWrapper{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A};
  unsigned mc = 0;  // Move command
  while (true) {
    std::cout << "Motion command: ";
    std::cin >> mc;
    std::cout << std::endl;
    motors.drive(static_cast<Direction>(mc));
  }
  return 0;
}
