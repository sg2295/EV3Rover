#include <gtest/gtest.h>
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

class MotorsTest : public ::testing::Test {
 protected:
  MotorsWrapper motors {ev3dev::OUTPUT_A, ev3dev::OUTPUT_B};
};

// TODO: Add below
TEST_F(MotorsTest, Forward) {
}

TEST_F(MotorsTest, North) {
}

TEST_F(MotorsTest, East) {
}

TEST_F(MotorsTest, West) {
}

TEST_F(MotorsTest, South) {
}

TEST_F(MotorsTest, NoMovement) {

}
