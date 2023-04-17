#include <memory>

#include "hardware.h"

#include "observation.h"
#include "motion.h"

namespace hardware {

using namespace motion;
using namespace observation;

EV3::EV3(ev3dev::address_type l_motor_add, ev3dev::address_type r_motor_add,
  ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add) :
    us_sensor{std::make_unique<USSensorWrapper>(us_motor_add, us_sensor_add)},
    motors{std::make_unique<MotorsWrapper>(l_motor_add, r_motor_add)} {}

EV3::~EV3() = default;

Sensing EV3::operator()(Direction d) {
  if (d != Direction::X) {
    motors->drive(d);
  }
  return Sensing{us_sensor->scan(), motors->cur_pose()};
}

}  // namespace hardware
