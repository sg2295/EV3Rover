#include <iostream>
#include <fstream>

#include "hardware.h"

#include "ev3dev.h"
#include "report.h"

using namespace hardware;

int main() {
  Log("Hardware test...\n");
  std::ofstream ofile{"outfile.txt"};
  EV3 ev3{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A, ev3dev::OUTPUT_C, ev3dev::INPUT_1};
  unsigned c = 0;
  unsigned i = 0;
  while (c < 5) {  // Quick hack to get things working
    auto s = ev3(static_cast<Direction>(c));
    ofile << s;  // Save to file...
    Log('[', i++, "] Odometry: x=", s.odometry.x, ", y=", s.odometry.y, ", theta=", s.odometry.theta, "Sensing: \n");
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
