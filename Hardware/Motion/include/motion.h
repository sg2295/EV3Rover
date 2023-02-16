#ifndef _MOTION_INCLUDE_MOTION_H_
#define _MOTION_INCLUDE_MOTION_H_

#include <memory>
#include <utility>

#include "hardware-scope.h"

namespace motion {

using hardware::Direction;
using hardware::Pose;

class MotorsWrapper {
 public:
  MotorsWrapper(ev3dev::address_type l_add, ev3dev::address_type r_add);
  ~MotorsWrapper();
  void drive(Direction dir);

  Pose odometry();

 private:
  std::unique_ptr<ev3dev::large_motor> l_motor;
  std::unique_ptr<ev3dev::large_motor> r_motor;
  static unsigned constexpr mov_dur_ms = 1000;
  static unsigned constexpr dflt_speed = 500;
  static float constexpr turn_s_dec = 0.5;  // % amount by which speed is reduced for a turn...
};

}  // namespace motion

#endif  // _MOTION_INCLUDE_MOTION_H_
