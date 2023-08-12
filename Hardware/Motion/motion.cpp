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
  Error(l_add != r_add, "Misconfigured motor connections");
  Error(r_motor->connected(), "Right motor not connected");
  Error(l_motor->connected(), "Left motor not connected");
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
  float constexpr wheel_circ = 17.59;  // in cm
  float constexpr distance_between_motors = 18.2;  // From center of the wheels  // Calculating from inner wheel bound = 15.4
  static_assert(mov_dur_ms == 1000, "Movement time has changed. Below needs to be generalized...");
  // Linear velocities (convert wheel speeds from degrees to centimeters):
  float const vl = wheel_circ * l_speed / 360;
  float const vr = wheel_circ * r_speed / 360;
  auto new_pose = Pose{};
  if (vr == vl) {  // Moving in a straight line
    new_pose.x = pose.x + vr * std::cos(pose.theta);
    new_pose.y = pose.y + vr * std::sin(pose.theta);
    new_pose.theta = pose.theta;
  } else {  // Turning
    float const R = (distance_between_motors / 2) * ((vr + vl) / (vr - vl));
    float const omega = (vr - vl) / distance_between_motors;  // Angular velocity
    // N.B. we could unroll the below to acquire the dx & dy (solving for pose.x/y)
    // https://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf
    // https://www.cs.bham.ac.uk/internal/courses/int-robot/2014/lectures/14-ir-kinematics.pdf
    float const icc_x = pose.x - R * std::sin(pose.theta);
    float const icc_y = pose.y + R * std::cos(pose.theta);
    // Log("R=", R, " omega=", omega, "\nicc_x=", icc_x, " icc_y=", icc_y, "\n");
    new_pose.x = (std::cos(omega) * (pose.x - icc_x)) - (std::sin(omega) * (pose.y - icc_y)) + icc_x;
    new_pose.y = (std::sin(omega) * (pose.x - icc_x)) + (std::cos(omega) * (pose.y - icc_y)) + icc_y;
    new_pose.theta = pose.theta + omega;
  }
  pose = new_pose;
}

Pose MotorsWrapper::cur_pose() const {
  return pose;
}

}  // namespace motion
