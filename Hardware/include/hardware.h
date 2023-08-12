#ifndef _HARDWARE_INCLUDE_HARDWARE_H_
#define _HARDWARE_INCLUDE_HARDWARE_H_

#include <array>
#include <iostream>
#include <memory>
#include <utility>

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
  Sensing(Observations obs, Pose odmtr) : observation{obs}, odometry{odmtr} {}

  Observations observation;
  Pose odometry;

  friend std::ostream& operator<<(std::ostream& os, Sensing const& s) {
    // Format: [pose], [observation] -> x, y, theta obs1 obs2 [...] obs9
    // Where obs has M observations
    os << s.odometry;
    for (auto const& bearing : s.observation)
      for (auto const obs : bearing)
        os << ' ' << obs;
    return os;
  }
};

class EV3 {
 public:
  EV3(ev3dev::address_type l_motor_add, ev3dev::address_type r_motor_add,
    ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  ~EV3();

  Sensing operator()(Direction d);

 private:
  std::unique_ptr<observation::USSensorWrapper> us_sensor;
  std::unique_ptr<motion::MotorsWrapper> motors;
};

}  // namespace hardware

#endif  // _HARDWARE_INCLUDE_HARDWARE_H_
