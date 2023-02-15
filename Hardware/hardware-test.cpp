#include "hardware.h"

#include "ev3dev.h"
#include "report.h"

using namespace hardware;

int main() {
  Log("Hardware test...\n");
  // TODO: Can move below into a motion test...
  // Main control loop here
  // auto motors = MotorsWrapper{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A};
  // auto sensor = USSensorWrapper{ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  // unsigned mc = 0;  // Move command
  // while (true) {
  //   std::cout << "Motion command: ";
  //   std::cin >> mc;
  //   std::cout << std::endl;
  //   motors.drive(static_cast<Direction>(mc));
  // }

  EV3 ev3{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A, ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  return 0;
}
