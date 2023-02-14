#include <memory>

#include "observation.h"
#include "ev3dev.h"

namespace observation {

using MM = ev3dev::medium_motor;
using USS = ev3dev::ultrasonic_sensor;

USSensorWrapper::USSensorWrapper(ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add) :
  motor{std::make_unique<MM>(us_motor_add)}, us_sensor{std::make_unique<USS>(us_sensor_add)} {}

float USSensorWrapper::scan() {
  auto reading = us_sensor->distance_centimeters();
  return reading;
}

void USSensorWrapper::rotate() {
  // TODO: Need to figure out logic re how the rotation works.
  //       To be more efficient start from one end and move to the other every time.
  //       Need to detect where we left off to go back the next reading. (L->R, then R->L).
  //       Instead of using the wheel encoder reading twice we could store the value in a short...
  int constexpr speed = 10;
  unsigned constexpr mov_dur_ms = 100;
  motor->set_speed_sp(speed).set_time_sp(mov_dur_ms).run_timed();
}

}  // namespace observation
