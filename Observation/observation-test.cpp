#include <iostream>

#include "report.h"

#include "observation.h"
#include "ev3dev.h"

using namespace observation;

int main() {
  Log("Starting observation test????", "123", " ok this works\n");
  // TODO: Test multiscan later on...
  std::cout << std::endl;
  return 0;
}
