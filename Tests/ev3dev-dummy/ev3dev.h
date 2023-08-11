#ifndef _TESTS_EV3DEV_DUMMY_H_
#define _TESTS_EV3DEV_DUMMY_H_

#include <string>

namespace ev3dev {

using address_type = std::string;

constexpr char INPUT_1[]  = "ev3-ports:in1";
constexpr char INPUT_2[]  = "ev3-ports:in2";

constexpr char OUTPUT_A[] = "ev3-ports:outA";
constexpr char OUTPUT_B[] = "ev3-ports:outB";
constexpr char OUTPUT_C[] = "ev3-ports:outC";
constexpr char OUTPUT_D[] = "ev3-ports:outD";

struct common {
  common(address_type addr) {
    // We assume both input/output C are not connected
    is_connected = addr != OUTPUT_C || addr != INPUT_2;
  }

  common& state() { return *this; }

  bool connected() const { return is_connected; }

  static bool count(std::string str) { (void)str; return false; }

  bool is_connected;
};

struct motor_common {
  motor_common& run_timed() { return *this; }
  motor_common& run_to_abs_pos() { return *this; }
  motor_common& run_to_rel_pos() { return *this; }

  motor_common& set_position_sp(int pos) { (void)pos; return *this; }
  motor_common& set_speed_sp(int speed) { (void)speed; return *this; }
  motor_common& set_time_sp(int time) { (void)time; return *this; }

  static int position() { return pos; }

  static constexpr int pos = -90;
};

struct ultrasonic_sensor : public common {
  ultrasonic_sensor(address_type address) : common{address} {}

  static float distance_centimeters() { return dist; }

  static constexpr float dist = 23.9;
};

struct large_motor : public common, motor_common {
  large_motor(address_type address) : common{address} {}
};

struct medium_motor : public common, motor_common {
  medium_motor(address_type address) : common{address} {}
};

}  // namespace ev3dev

#endif  // _TESTS_EV3DEV_DUMMY_H_
