#include <iostream>

#include "hardware.h"
#include "ev3dev.h"

using hardware::EV3;

int main() {
  EV3 ev3{ev3dev::OUTPUT_D, ev3dev::OUTPUT_A, ev3dev::OUTPUT_C, ev3dev::INPUT_1};  // Init EV3
  // Main loop below:

  // 1. Move EV3, get sensor reading and odometry -- Done
  // 2. Construct multiscan from previous X positions -- TODO: need to place points relative to origin...
  // 3. Extract the line segments from the scan
  // 4. For each segment:
  //      Associate line segments
  //      Create constraint and add to graph
  // 5. Save graph
  // 6. Optimize the graph
  // 7. If graph is not consistent, remove new contraints (from above) and restore state
  //    Else update line segment endpoints (see below)

  // Update endpoints:
  // for each landmark (line segment):
  //   Init s1=+inf, s2=-inf
  //   Calculate vector representation
  return 0;
}
