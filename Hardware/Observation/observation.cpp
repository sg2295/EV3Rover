#include <memory>
#include <chrono>
#include <thread>

#include "report.h"

#include "observation.h"
#include "ev3dev.h"

namespace observation {

using MM = ev3dev::medium_motor;
using USS = ev3dev::ultrasonic_sensor;
using SensorReading = std::array<float, USSensorWrapper::num_measurements>;

USSensorWrapper::USSensorWrapper(ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add) :
    motor{std::make_unique<MM>(us_motor_add)}, us_sensor{std::make_unique<USS>(us_sensor_add)} {
  Assert(us_sensor->connected(), "Sensor not connected");
  Assert(motor->connected(), "Motor not connected");
  // Reset motor to starting position...
  motor->set_position_sp(m_start_pos);
  motor->set_speed_sp(m_speed).run_to_abs_pos();
  while (motor->state().count("running"))
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  Assert(motor->position() == m_start_pos, "Motor position invalid in ctor.");
}

USSensorWrapper::~USSensorWrapper() = default;

float USSensorWrapper::bearing_reading() {
  // Gets an average for the readings...
  // TODO: Is there a better way to deal with inf? Should we discard them?
  float bearing_reading = 0;
  for (unsigned i = 0; i < num_measurements_per_bearing; ++i) {
    bearing_reading += us_sensor->distance_centimeters();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return bearing_reading / num_measurements_per_bearing;
}

SensorReading USSensorWrapper::scan() {
  auto readings = std::array<float, num_measurements>{};
  // To save power (& time) rotating sensor back to other side, we will do a sweep from whichever
  // side we left off. E.g. L->R and then R->L (see `invert` below).
  bool invert = motor->position() > 0;
  for (unsigned i = 0; i < num_measurements; ++i) {
    readings.at(invert ? num_measurements - 1 - i : i) = bearing_reading();
    // Log("Reading done at: ", motor->position(), "\n");
    if (i + 1 < num_measurements) rotate(invert);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  // Unoptimized scan() version:
  // Reset motor to starting position
  // motor->set_position_sp(m_start_pos);
  // motor->set_speed_sp(m_speed).run_to_abs_pos();
  // while (motor->state().count("running"))
  //   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // // Do scan
  // for (unsigned i = 0; i < num_measurements; ++i) {
  //   readings.at(i) = bearing_reading();  // us_sensor->distance_centimeters();
  //   // Log("Reading done at: ", motor->position(), "\n");
  //   if (i + 1 < num_measurements) rotate(false);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // }
  Warn(abs(motor->position()) == abs(m_start_pos), "Motor position after scan invalid.");
  return readings;
}

void USSensorWrapper::rotate(bool invert) {
  // Default is clockwise. Set `invert` to go counter-clockwise.
  static_assert(m_pos_inc * (num_measurements - 1) == 180, "Sensor inc and num_entries do not match...");
  motor->set_position_sp(invert ? -m_pos_inc : m_pos_inc);  //  +/- angle change
  motor->set_speed_sp(invert ? -m_speed : m_speed).run_to_rel_pos();
  while (motor->state().count("running"))
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

}  // namespace observation
