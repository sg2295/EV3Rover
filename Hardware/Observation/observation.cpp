#include <memory>
#include <chrono>
#include <thread>

#include "report.h"

#include "observation.h"
#include "ev3dev.h"

namespace observation {

using MM = ev3dev::medium_motor;
using USS = ev3dev::ultrasonic_sensor;

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

BearingReading USSensorWrapper::bearing_reading() {
  auto bearing_reading = BearingReading{};
  for (unsigned i = 0; i < bearing_reading.size(); ++i) {
    bearing_reading.at(i) = us_sensor->distance_centimeters();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return bearing_reading;
}

SensorReading USSensorWrapper::scan() {
  auto readings = SensorReading{};
  // To save power (& time) rotating sensor back to other side, we will do a sweep from whichever
  // side we left off. E.g. L->R and then R->L (see `invert` below).
  bool invert = motor->position() > 0;
  for (unsigned i = 0; i < readings.size(); ++i) {
    readings.at(invert ? readings.size() - 1 - i : i) = bearing_reading();
    Log("Reading done at: ", motor->position(), "\n");
    if (i + 1 < readings.size()) rotate(invert);
    // Warn(abs(motor->position()) % 15, "Motor position is not correct");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  // TODO: Remove below before tapeout
  // Unoptimized scan() version:
  // Reset motor to starting position
  // motor->set_position_sp(m_start_pos);
  // motor->set_speed_sp(m_speed).run_to_abs_pos();
  // while (motor->state().count("running"))
  //   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // // Do scan
  // for (unsigned i = 0; i < readings.size(); ++i) {
  //   readings.at(i) = bearing_reading();  // us_sensor->distance_centimeters();
  //   // Log("Reading done at: ", motor->position(), "\n");
  //   if (i + 1 < readings.size()) rotate(false);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // }
  Warn(abs(motor->position()) == abs(m_start_pos), "Motor position after scan invalid.");
  return readings;
}

void USSensorWrapper::rotate(bool invert) {
  unsigned constexpr num_measurements = hardware::HardwareConstants::NUM_READINGS;
  unsigned constexpr sensor_fov = hardware::HardwareConstants::SENSOR_FOV;
  static_assert(m_pos_inc * (num_measurements - 1) == sensor_fov, "Sensor increment and number of entries do not match...");
  motor->set_position_sp(invert ? -m_pos_inc : m_pos_inc);  //  +/- angle change
  motor->set_speed_sp(invert ? -m_speed : m_speed).run_to_rel_pos();
  while (motor->state().count("running"))
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

}  // namespace observation
