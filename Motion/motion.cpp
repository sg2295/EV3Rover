#include <memory>

#include <chrono>
#include <thread>

#include "motion.h"
#include "ev3dev.h"

#include "report.h"

namespace motion {

using LM = ev3dev::large_motor;

MotorsWrapper::MotorsWrapper(ev3dev::address_type l_add, ev3dev::address_type r_add) :
  l_motor{std::make_unique<LM>(l_add)}, r_motor{std::make_unique<LM>(r_add)} {
    Assert(r_motor->connected(), "Right motor not connected");
    Assert(l_motor->connected(), "Left motor not connected");
  }

void MotorsWrapper::drive(Direction dir) {
  int const speed = (dir != Direction::S) ? dflt_speed : -dflt_speed;
  l_motor->set_speed_sp((dir != Direction::NW) ? speed : (speed * turn_s_dec)).set_time_sp(mov_dur_ms).run_timed();
  r_motor->set_speed_sp((dir != Direction::NE) ? speed : (speed * turn_s_dec)).set_time_sp(mov_dur_ms).run_timed();
  while (l_motor->state().count("running") || r_motor->state().count("running"))
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
}  // namespace motion
