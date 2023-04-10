#include "bunny/angle.h"

#include <fmt/format.h>

bunny::bu_str bunny::math::format_as_angle(bunny::f64 const value, bunny::f64 const degrees) {
  return fmt::format("[Angle({0:.9} rad | {1:.9} deg)]", value, degrees);
}
bunny::bu_str bunny::math::format_as_angle(bunny::f32 const value, bunny::f32 const degrees) {
  return fmt::format("[Angle({0:.9} rad | {1:.9} deg)]", value, degrees);
}
