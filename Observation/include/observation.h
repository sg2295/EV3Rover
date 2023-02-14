#include <memory>

namespace ev3dev {
  class medium_motor;
  class ultrasonic_sensor;
  using address_type = std::string;  // TODO: Should this be a typedef instead?
}  // namespace ev3dev

namespace observation {

class USSensorWrapper {
 public:
  USSensorWrapper(ev3dev::address_type us_motor_add, ev3dev::address_type us_sensor_add);
  float scan();

 private:
  void rotate();

  std::unique_ptr<ev3dev::medium_motor> motor;
  std::unique_ptr<ev3dev::ultrasonic_sensor> us_sensor;
};

}  // namespace observation
