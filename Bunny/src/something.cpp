#include "bunny/core.h"

#include <iostream>

// The MAIN function, from here we start the application and run the game loop
int main() {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  auto t           = 15_s;
  bunny::KeyCode b = bunny::KeyCode::Enter;
  std::cout << "t: " << t << std::endl;
  std::cout << "b: " << b << std::endl;
  return 0;
}