#include <memory>
#include <utility>
#include <cmath>
#include <chrono>
#include <thread>

#include "motion.h"
#include "ev3dev.h"

#include "report.h"

namespace motion {

using LM = ev3dev::large_motor;

MotorsWrapper::MotorsWrapper(ev3dev::address_type l_add, ev3dev::address_type r_add) :
    l_motor{std::make_unique<LM>(l_add)}, r_motor{std::make_unique<LM>(r_add)}, pose{} {
  Assert(r_motor->connected(), "Right motor not connected");
  Assert(l_motor->connected(), "Left motor not connected");
}

MotorsWrapper::~MotorsWrapper() = default;

void MotorsWrapper::drive(Direction dir) {
  if (dir == Direction::X) return;  // No move command
  int const speed = (dir != Direction::S) ? dflt_speed : -dflt_speed;
  int l_speed = (dir != Direction::NW) ? speed : (speed * turn_s_dec);
  int r_speed = (dir != Direction::NE) ? speed : (speed * turn_s_dec);
  l_motor->set_speed_sp(l_speed).set_time_sp(mov_dur_ms).run_timed();
  r_motor->set_speed_sp(r_speed).set_time_sp(mov_dur_ms).run_timed();
  while (l_motor->state().count("running") || r_motor->state().count("running"))
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  update_pose(l_speed, r_speed);
}

void MotorsWrapper::update_pose(int l_speed, int r_speed) {
  // TODO: Complete update pose function.
  // We can use `mov_dur_ms`
  // count_per_m();  // Tacho counts per meter of travel.
  // full_travel_count();  // Total number of tacho counts. Combine with count_per_m() to get total meters travelled.
  float constexpr wheel_circ = 17.59;  // in cm
  float constexpr distance_between_motors = 15.4;
  float const dl = wheel_circ * l_speed / dflt_speed;
  float const dr = wheel_circ * r_speed / dflt_speed;
  float d = (dl + dr) / 2;
  float delta_theta = (dr - dl) / distance_between_motors;
  float new_theta = pose.theta + delta_theta;
  float constexpr pi = 3.14;
  // If new_theta
  float new_x = (new_theta < pi / 2 && new_theta > 3 * pi / 2) ? pose.x + d * std::cos(pose.theta) : pose.x - d * std::cos(pose.theta);
  float new_y = (new_theta < pi && new_theta > 0) ? pose.y + d * std::sin(pose.theta) : pose.y - d * std::sin(pose.theta);
  auto new_pose = Pose{static_cast<int>(new_x), static_cast<int>(new_y), new_theta};
  // auto new_pose = Pose{
  //   static_cast<int>(pose.x + d * std::cos(pose.theta)), static_cast<int>(pose.y + d * std::sin(pose.theta)),
  //   new_theta};
  pose = new_pose;
}

Pose MotorsWrapper::odometry() const {
  return pose;
}

}  // namespace motion
