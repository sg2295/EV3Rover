#include <iostream>
#include <fstream>

#include "hardware.h"

#include "ev3dev.h"
#include "report.h"

int main() {
  Log("Beginning exploration...\n");
  std::ofstream ofile{"outfile.txt"};
  hardware::EV3 ev3{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A, ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  unsigned c = 0;  // Move command
  // N.B. Enums are expressed as `unsigned int` under the hood. This is the most efficient & effective way of encoding commands.
  unsigned i = 0;  // Pose/Scan pair number
  while (c < 5) {
    auto s = ev3(static_cast<hardware::Direction>(c));
    ofile << s;  // Save to file...
    Log('[', ++i, "] Odometry: x=", s.odometry.x, ", y=", s.odometry.y, ", theta=", s.odometry.theta, "Sensing: \n");
    for (auto const& bearing : s.observation) {
      Log('\t');
      for (float const f : bearing)
        Log(f, ' ');
      Log('\n');
    }
    Log("\nMotion command: ");
    std::cin >> c;
    Log('\n');
  }
  ofile << std::endl;
  ofile.close();
  Log("Successfully closed the outfile\n");
  return 0;
}
