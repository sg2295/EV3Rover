#include <gtest/gtest.h>
#include <cmath>
#include <string>

#include "motion.h"
#include "ev3dev.h"

using namespace motion;

class MotorsConstructorTest : public ::testing::Test {};

TEST_F(MotorsConstructorTest, ValidConnection) {
  MotorsWrapper motors {ev3dev::OUTPUT_A, ev3dev::OUTPUT_B};
  EXPECT_EQ(motors.cur_pose(), Pose{});
}

TEST_F(MotorsConstructorTest, InvalidConnection) {
  // TODO: Add
  // EXPECT_DEATH({ MotorsWrapper{ev3dev::OUTPUT_A, ev3dev::OUTPUT_C}; }, "");
}

TEST_F(MotorsConstructorTest, InvalidConnections) {
  // TODO: Add
  // EXPECT_DEATH({ MotorsWrapper{ev3dev::OUTPUT_C, ev3dev::OUTPUT_D}; }, "");
}

TEST_F(MotorsConstructorTest, DuplicateConnection) {
  // TODO: Add functionality and test
  // EXPECT_DEATH({ MotorsWrapper{ev3dev::OUTPUT_A, ev3dev::OUTPUT_A}; }, "");
  // EXPECT_DEATH({ MotorsWrapper{ev3dev::OUTPUT_C, ev3dev::OUTPUT_C}; }, "");
}

class MotorsTest : public ::testing::Test {
 protected:
  MotorsWrapper motors {ev3dev::OUTPUT_A, ev3dev::OUTPUT_B};
};

TEST_F(MotorsTest, North) {
  EXPECT_EQ(motors.cur_pose(), Pose{});
  motors.drive(Direction::N);

  auto exp_pose = Pose{8.795, 0, 0};
  EXPECT_EQ(motors.cur_pose(), exp_pose);
}

TEST_F(MotorsTest, NorthEast) {
  EXPECT_EQ(motors.cur_pose(), Pose{});
  motors.drive(Direction::NE);

  float constexpr exp_R = - 9.1 * 13.1925 / 4.3975;
  float constexpr exp_omega = -4.3975 / 18.2;
  float const exp_x = std::sin(exp_omega) * exp_R;
  float const exp_y = exp_R - (std::cos(exp_omega) * exp_R);
  auto exp_pose = Pose{exp_x, exp_y, exp_omega};

  EXPECT_FLOAT_EQ(motors.cur_pose().x, exp_pose.x);
  EXPECT_FLOAT_EQ(motors.cur_pose().y, exp_pose.y);
  EXPECT_FLOAT_EQ(motors.cur_pose().theta, exp_pose.theta);
}

TEST_F(MotorsTest, NorthWest) {
  EXPECT_EQ(motors.cur_pose(), Pose{});
  motors.drive(Direction::NW);

  float constexpr exp_R = 9.1 * 13.1925 / 4.3975;
  float constexpr exp_omega = 4.3975 / 18.2;
  float const exp_x = std::sin(exp_omega) * exp_R;
  float const exp_y = exp_R - (std::cos(exp_omega) * exp_R);

  auto exp_pose = Pose{exp_x, exp_y, exp_omega};
  EXPECT_FLOAT_EQ(motors.cur_pose().x, exp_pose.x);
  EXPECT_FLOAT_EQ(motors.cur_pose().y, exp_pose.y);
  EXPECT_FLOAT_EQ(motors.cur_pose().theta, exp_pose.theta);
}

TEST_F(MotorsTest, South) {
  EXPECT_EQ(motors.cur_pose(), Pose{});
  motors.drive(Direction::S);

  auto exp_pose = Pose{-8.795, 0, 0};
  EXPECT_EQ(motors.cur_pose(), exp_pose);
}

TEST_F(MotorsTest, NoMovement) {
  EXPECT_EQ(motors.cur_pose(), Pose{});
  motors.drive(Direction::X);
  EXPECT_EQ(motors.cur_pose(), Pose{});
}
