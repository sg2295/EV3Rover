#include <memory>

namespace ev3dev {
  class large_motor;
  using address_type = std::string;  // TODO: Should this be a typedef instead?
}  // namespace ev3dev

namespace motion {

enum Direction {
  N = 0, NE = 1, NW = 2, S = 3
};

class MotorsWrapper {
 public:
  MotorsWrapper(ev3dev::address_type l_add, ev3dev::address_type r_add);

  void drive(Direction dir);

  unsigned odometry();  // TODO: Get odometry from wheel encoders...

 private:
  std::unique_ptr<ev3dev::large_motor> l_motor;
  std::unique_ptr<ev3dev::large_motor> r_motor;
};

}  // namespace motion
