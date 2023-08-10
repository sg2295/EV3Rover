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
  bool connected() const { return addr != OUTPUT_C; }

  common& set_speed_sp(int speed) { (void) speed; return *this; }
  common& set_time_sp(int time) { (void) time; return *this; }
  common& run_timed() { return *this; }
  common& state() { return *this; }
  static bool count(std::string str) { (void) str; return false; }

  address_type addr{};
};

struct ultrasonic_sensor : public common {
  ultrasonic_sensor(address_type address) : common{address} {}
};

struct large_motor : public common {
  large_motor(address_type address) : common{address} {}
};

// TODO: Add dummy versions for observation components
struct medium_motor;

}  // namespace ev3dev

#endif  // _TESTS_EV3DEV_DUMMY_H_
