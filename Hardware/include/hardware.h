#ifndef _HARDWARE_INCLUDE_HARDWARE_H_
#define _HARDWARE_INCLUDE_HARDWARE_H_

#include <memory>
#include <array>
#include <utility>
#include <deque>

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
  Sensing(std::array<float, HardwareConstants::NUM_READINGS> obs, Pose odmtr) :
    observation{obs}, odometry{odmtr} {}

  std::array<float, HardwareConstants::NUM_READINGS> observation;
  Pose odometry;
};

class EV3 {
 public:
  EV3(ev3dev::address_type l_motor_add, ev3dev::address_type r_motor_add,
    ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  ~EV3();

  Sensing operator()(Direction d);
  std::deque<Sensing> const& get_readings() const { return readings; }

 private:
  std::unique_ptr<observation::USSensorWrapper> us_sensor;
  std::unique_ptr<motion::MotorsWrapper> motors;
  std::deque<Sensing> readings;
};

}  // namespace hardware

#endif  // _HARDWARE_INCLUDE_HARDWARE_H_
