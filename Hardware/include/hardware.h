#ifndef _HARDWARE_INCLUDE_HARDWARE_H_
#define _HARDWARE_INCLUDE_HARDWARE_H_

#include <memory>
#include <array>
#include <utility>
#include <deque>
#include <iostream>

#include "hardware-scope.h"

namespace ev3dev {
  using address_type = std::string;
}  // namespace ev3dev

namespace observation {
class USSensorWrapper;
}  // namespace observation

namespace motion {
class MotorsWrapper;
}  // namespace motion

namespace hardware {

struct Sensing {
  Sensing() = default;
  // TODO: Fix the below - need to restructure dependencies...
  Sensing(Observations obs, Pose odmtr) : observation{obs}, odometry{odmtr} {}

  Observations observation;
  Pose odometry;

  friend std::ostream& operator<<(std::ostream& os, Sensing const& s) {
    // Format: [pose], [observation] -> x, y, theta obs1 obs2 [...] obs9
    // Where obsN has M observations
    os << s.odometry.x << ' ' << s.odometry.y << ' ' << s.odometry.theta;
    for (auto const& bearing : s.observation)
      for (auto const obs : bearing)
        os << ' ' << obs;
    // TODO: Do we want to keep flushing after each line, or should we flush only in the end?
    //       (To avoid any overheads...)
    os << std::endl;
    return os;
  }
};

class EV3 {
 public:
  EV3(ev3dev::address_type l_motor_add, ev3dev::address_type r_motor_add,
    ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  ~EV3();

  Sensing operator()(Direction d);
  // std::deque<Sensing> const& get_readings() const { return readings; }

 private:
  std::unique_ptr<observation::USSensorWrapper> us_sensor;
  std::unique_ptr<motion::MotorsWrapper> motors;
  // std::deque<Sensing> readings;  // We're saving to file instead...
};

}  // namespace hardware

#endif  // _HARDWARE_INCLUDE_HARDWARE_H_
