#ifndef _OBSERVATION_INCLUDE_OBSERVATION_H_
#define _OBSERVATION_INCLUDE_OBSERVATION_H_

#include <memory>
#include <array>

#include "hardware-scope.h"

namespace observation {

class USSensorWrapper {
 public:
  USSensorWrapper(ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  ~USSensorWrapper();
  static size_t constexpr num_measurements = 13;  // 0..180 (a measurement every 15 degrees)
  std::array<float, num_measurements> scan();

 private:  // TODO: Make private again!!!
  float bearing_reading();
  void rotate(bool invert);
  static int constexpr m_speed = 75;
  static int constexpr m_start_pos = -90;  // Initial starting position of sensor (degrees)
  static int constexpr m_pos_inc = 15;  // Degree increment during scan
  static unsigned constexpr num_measurements_per_bearing = 10;  // Number of readings per bearing (we use the average!)
  std::unique_ptr<ev3dev::medium_motor> motor;
  std::unique_ptr<ev3dev::ultrasonic_sensor> us_sensor;
};

}  // namespace observation

#endif  // _OBSERVATION_INCLUDE_OBSERVATION_H_
