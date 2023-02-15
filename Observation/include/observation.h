#ifndef _OBSERVATION_INCLUDE_OBSERVATION_H_
#define _OBSERVATION_INCLUDE_OBSERVATION_H_

#include <memory>
#include <array>

namespace ev3dev {
  class medium_motor;
  class ultrasonic_sensor;
  using address_type = std::string;
}  // namespace ev3dev

namespace observation {

class USSensorWrapper {
 public:
  USSensorWrapper(ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  static size_t constexpr num_measurements = 13;  // 0..180 (a measurement every 15 degrees)
  std::array<float, num_measurements> scan();

 public:  // TODO: Make private again!!!
  void rotate(bool invert);
  static int constexpr m_speed = 75;
  static int constexpr m_start_pos = -90;  // Initial starting position of sensor (degrees)
  static int constexpr m_pos_inc = 15;  // Degree increment during scan
  std::unique_ptr<ev3dev::medium_motor> motor;
  std::unique_ptr<ev3dev::ultrasonic_sensor> us_sensor;
};

}  // namespace observation

#endif  // _OBSERVATION_INCLUDE_OBSERVATION_H_
