#ifndef _HARDWARE_INCLUDE_SCOPE_H_
#define _HARDWARE_INCLUDE_SCOPE_H_

#include <string>
#include <iostream>

// Fwd declarations used by hardware modules
namespace ev3dev {
class large_motor;
class medium_motor;
class ultrasonic_sensor;
using address_type = std::string;
}  // namespace ev3dev

namespace hardware {

// Move direction
enum Direction {
  // X = no move command - remain static
  X = 0, N = 1, NE = 2, NW = 3, S = 4
};

enum HardwareConstants {
  NUM_READINGS = 13,  // Number of positions we get a reading from
  NUM_READINGS_PER_BEARING = 25,  // Number of sensor measurements per angle
  SENSOR_FOV = 180,  // Field of view for a single scan (in degrees)
};

struct Pose {
  float x;
  float y;
  float theta;

  bool operator==(const Pose& other) const {
    return x == other.x && y == other.y && theta == other.theta;
  }
  friend std::ostream& operator<<(std::ostream& os, Pose const& pose) {
    os << pose.x << ' ' << pose.y << ' ' << pose.theta;
    return os;
  }
};

using Observations = std::array<std::array<float, HardwareConstants::NUM_READINGS_PER_BEARING>, HardwareConstants::NUM_READINGS>;

}  // namespace hardware

#endif  // _HARDWARE_INCLUDE_SCOPE_H_
