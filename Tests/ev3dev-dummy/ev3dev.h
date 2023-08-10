#ifndef _TESTS_EV3DEV_DUMMY_H_
#define _TESTS_EV3DEV_DUMMY_H_

#include <string>

namespace ev3dev {

using address_type = std::string;

constexpr char OUTPUT_A[] = "ev3-ports::outA";
constexpr char OUTPUT_B[] = "ev3-ports:outB";
constexpr char OUTPUT_C[] = "ev3-ports:outC";

struct common {
  common(address_type addr) : addr{addr} {}
  // We assume output C is not connected
  // TODO: will need to add INPUT_C too for observation
  bool connected() { return addr != OUTPUT_C; }

  address_type addr{};
};

struct ultrasonic_sensor : public common {
  ultrasonic_sensor(address_type address) : common{address} {}
};

struct large_motor : public common {
  large_motor(address_type address) : common{address} {}
};

struct medium_motor;


}  // namespace ev3dev

#endif  // _TESTS_EV3DEV_DUMMY_H_
