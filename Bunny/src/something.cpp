#include "bunny/core.h"

#include <iostream>

int main() {
  std::cout << "Hey there, testing shit" << std::endl;
  auto t = 30.1234567890123456789_s;
  std::cout << "Here's t: " << t << std::endl;
  std::cout << "Here's 2 t: " << 2 * t << std::endl;
  std::cout << "Here's t / 2: " << t / 2 << std::endl;
  return 0;
}
