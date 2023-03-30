#ifndef _OBSERVATION_INCLUDE_OBSERVATION_H_
#define _OBSERVATION_INCLUDE_OBSERVATION_H_

#include <memory>
#include <array>

#include "hardware-scope.h"

namespace observation {

using BearingReading = std::array<float, hardware::HardwareConstants::NUM_READINGS_PER_BEARING>;
using SensorReading = std::array<BearingReading, hardware::HardwareConstants::NUM_READINGS>;

class USSensorWrapper {
 public:
  USSensorWrapper(ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  ~USSensorWrapper();
  SensorReading scan();

 private:
  BearingReading bearing_reading();
  void rotate(bool invert);
  static int constexpr m_speed = 75;
  static int constexpr m_start_pos = -90;  // Initial starting position of sensor (degrees)
  static int constexpr m_pos_inc = 15;  // Degree increment during scan
  std::unique_ptr<ev3dev::medium_motor> motor;
  std::unique_ptr<ev3dev::ultrasonic_sensor> us_sensor;
};

}  // namespace observation

#endif  // _OBSERVATION_INCLUDE_OBSERVATION_H_
