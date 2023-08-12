#include <iostream>
#include <fstream>

#include "hardware.h"

#include "ev3dev.h"
#include "report.h"

int main() {
  Log("Beginning exploration...\n");
  std::ofstream ofile{"outfile.txt"};
  hardware::EV3 ev3{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A, ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  unsigned cmd_code = 0;  // Move command (express `Direction` enum as integers)
  unsigned pose_num = 0;  // Pose/Scan pair number
  while (cmd_code < 5) {
    auto s = ev3(static_cast<hardware::Direction>(cmd_code));
    ofile << s << std::endl;  // Save to file...
    Log('[', ++pose_num, "] x=", s.odometry.x, ", y=", s.odometry.y, ", theta=", s.odometry.theta, " scan: \n");
    for (auto const& bearing : s.observation) {
      Log('\t');
      for (float const f : bearing)
        Log(f, ' ');
      Log('\n');
    }
    Log("\nMotion command: ");
    std::cin >> cmd_code;
    Log('\n');
  }
  ofile << std::endl;
  ofile.close();
  Log("Successfully closed the outfile\n");
  return 0;
}
