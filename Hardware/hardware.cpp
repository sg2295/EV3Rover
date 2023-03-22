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
    motors{std::make_unique<MotorsWrapper>(l_motor_add, r_motor_add)} {}  // , readings{} {}

EV3::~EV3() = default;

Sensing EV3::operator()(Direction d) {
  if (d != Direction::X) {
    motors->drive(d);
  }
  return Sensing{us_sensor->scan(), motors->odometry()};
  // ! Remove the below after we save to file !
  // readings.push_front(Sensing{us_sensor->scan(), motors->odometry()});
  // if (readings.size() >= HardwareConstants::NUM_MULTISCAN)
  //   readings.pop_back();
  // return readings.front();
}

}  // namespace hardware
