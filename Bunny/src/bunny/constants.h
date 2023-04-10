#pragma once
#include "bunny/typedefs.h"

#include <numbers>
namespace bunny {
  namespace constants {
    constexpr f64 TWO_PI = std::numbers::pi * 2;
    constexpr f64 PI     = std::numbers::pi;
    constexpr f64 PI_2   = std::numbers::pi / 2.;
    constexpr f64 PI_4   = std::numbers::pi / 4.;
    constexpr f64 PI_INV = std::numbers::inv_pi;
  }  // namespace constants
}  // namespace bunny
