#ifndef _HARDWARE_INCLUDE_SCOPE_H_
#define _HARDWARE_INCLUDE_SCOPE_H_

#include <string>

// Fwd declarations used by hardware modules
namespace ev3dev {
  class large_motor;
  class medium_motor;
  class ultrasonic_sensor;
  using address_type = std::string;  // TODO: Should this be a typedef instead?
}  // namespace ev3dev

#endif  // _HARDWARE_INCLUDE_SCOPE_H_
