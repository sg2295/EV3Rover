#include <chrono>
#include <thread>

#include "motor.h"
#include "ev3dev.h"

namespace motion {

using LM = ev3dev::large_motor;

MotorsWrapper::MotorsWrapper(ev3dev::address_type l_add, ev3dev::address_type r_add) :
  l_motor{std::make_unique<LM>(l_add)}, r_motor{std::make_unique<LM>(r_add)} {}

void MotorsWrapper::drive(Direction dir) {
  unsigned constexpr mov_dur_ms = 1000;
  int const speed = (dir != Direction::S) ? 500 : -500;
  l_motor->set_speed_sp((dir != NW) ? speed : (speed * 0.50)).set_time_sp(mov_dur_ms).run_timed();
  r_motor->set_speed_sp((dir != NE) ? speed : (speed * 0.50)).set_time_sp(mov_dur_ms).run_timed();
  // TODO: Is the below needed?
  while (l_motor->state().count("running") || r_motor->state().count("running"))
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
}  // namespace motion
