#include <iostream>
#include <fstream>

#include "hardware.h"

#include "ev3dev.h"
#include "report.h"

using namespace hardware;

int main() {
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
  Log("Hardware test...\n");
  std::ofstream ofile{"outfile.txt"};
  EV3 ev3{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A, ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  unsigned c = 0;
  while (c < 5) {  // Quick hack to get things working
    auto s = ev3(static_cast<Direction>(c));
    ofile << s;  // Save to file...
    Log("Odometry: x=", s.odometry.x, ", y=", s.odometry.y, ", theta=", s.odometry.theta, '\n');
    Log("Sensing: ");
    for (float f : s.observation)
      Log(f, ' ');
    Log("\nMotion command: ");
    std::cin >> c;
    Log('\n');
  }
  ofile << std::endl;
  ofile.close();
  Log("Successfully closed the outfile\n");
  return 0;
}
