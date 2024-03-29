#include <gtest/gtest.h>

#include "observation.h"
#include "ev3dev.h"

#include "report.h"

using namespace observation;

class USSensorConstructorTest : public ::testing::Test {
 public:
  USSensorConstructorTest() {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  }
};

TEST_F(USSensorConstructorTest, InvalidInput) {
  EXPECT_DEATH(USSensorWrapper(ev3dev::OUTPUT_A, ev3dev::INPUT_2), "Error: Sensor not connected .*");
}

TEST_F(USSensorConstructorTest, InvalidOutput) {
  EXPECT_DEATH(USSensorWrapper(ev3dev::OUTPUT_C, ev3dev::INPUT_1), "Error: Motor not connected .*");
}

class USSensorTest : public ::testing::Test {};

TEST_F(USSensorTest, Scan) {
  USSensorWrapper us_sensor{ev3dev::OUTPUT_A, ev3dev::INPUT_1};
  auto scan = us_sensor.scan();
  float dist = 0;
  for (auto bearing : scan) {
    for (auto entry : bearing) {
      ++dist;
      EXPECT_FLOAT_EQ(entry, dist);
    }
  }
}

TEST_F(USSensorTest, DoubleScan) {
  USSensorWrapper us_sensor{ev3dev::OUTPUT_A, ev3dev::INPUT_1};
  auto scan1 = us_sensor.scan();
  float dist = 0;
  for (auto bearing : scan1) {
    for (auto entry : bearing) {
      ++dist;
      EXPECT_FLOAT_EQ(entry, dist);
    }
  }
  // Notice the second scan is reversed since it's going R -> L
  auto scan2 = us_sensor.scan();
  for (size_t i = scan2.size(); i > 0; --i) {
    for (auto entry : scan2.at(i - 1)) {
      ++dist;
      EXPECT_FLOAT_EQ(entry, dist);
    }
  }
}
