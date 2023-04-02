#include "bupch.h"

#include "bunny/math/angle.h"

#include <iostream>


int main() {
  Bunny::math::angle a = 90_deg;
  std::cout << "Hello World!"
            << "Rad: \n"
            << a.as_rad()
            << ", Deg: \n"
            << a.as_deg()
            << "!!!";
}