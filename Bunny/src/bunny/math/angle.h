#pragma once

#include "bunny/core/typedefs.h"
#include "constants.h"
namespace Bunny {
  namespace math {
    struct angle {
     private:
      bu_f32 value;

     public:
      explicit angle() :
          value{0} {}
      explicit angle(bu_f32 v) :
          value{v} {}

      bu_f32 as_deg() {

        return value / static_cast<float>(constants::PI);
      }
      bu_f32 as_rad() {
        return value;
      }
      bu_f32 sin() {
        return ::sin(value);
      }
      bu_f32 cos() {
        return ::cos(value);
      }

      angle& operator+=(bu_f32 v) {
        value += v;
        return *this;
      }

      angle& operator-=(bu_f32 v) {
        value -= v;
        return *this;
      }
      angle& operator+=(angle v) {
        value += v.value;
        return *this;
      }

      angle& operator-=(angle v) {
        value -= v.value;
        return *this;
      }

      angle& operator*=(bu_f32 v) {
        value *= v;
        return *this;
      }

      angle& operator/=(bu_f32 v) {
        value /= v;
        return *this;
      }


      angle operator-() {
        return angle(-value);
      }
      friend angle operator+(angle a, angle b) {
        return angle(a.as_rad() + b.as_rad());
      }
      friend angle operator-(angle a, angle b) {
        return angle(a.as_rad() - b.as_rad());
      }
      friend angle operator+(angle a, bu_f32 b) {
        return angle(a.as_rad() + b);
      }
      friend angle operator-(angle a, bu_f32 b) {
        return angle(a.as_rad() - b);
      }
      friend angle operator*(angle a, bu_f32 b) {
        return angle(a.as_rad() * b);
      }
      friend angle operator*(bu_f32 b, angle a) {
        return angle(a.as_rad() * b);
      }
      friend angle operator/(angle a, bu_f32 b) {
        return angle(a.as_rad() / b);
      }

      bool operator==(angle b) {
        return value == b.value;
      }
      bool operator!=(angle b) {
        return value != b.value;
      }
      bool operator>(angle b) {
        return value > b.value;
      }
      bool operator<(angle b) {
        return value < b.value;
      }
      bool operator<=(angle b) {
        return value <= b.value;
      }
      bool operator>=(angle b) {
        return value >= b.value;
      }
      static angle from_deg(bu_f32 v) {
        return angle(v * static_cast<float>(constants::PI));
      }
      static angle from_rad(bu_f32 v) {
        return angle(v);
      }
    };
  }  // namespace math
}  // namespace Bunny
Bunny::math::angle inline operator"" _deg(long double f) {
  return Bunny::math::angle((Bunny::bu_f32)f * static_cast<Bunny::bu_f32>(Bunny::math::constants::PI));
}
Bunny::math::angle inline operator"" _deg(unsigned long long int f) {
  return Bunny::math::angle((Bunny::bu_f32)f * static_cast<Bunny::bu_f32>(Bunny::math::constants::PI));
}
Bunny::math::angle inline operator"" _rad(long double f) {
  return Bunny::math::angle((Bunny::bu_f32)f);
}
Bunny::math::angle inline operator"" _rad(unsigned long long int f) {
  return Bunny::math::angle((Bunny::bu_f32)f);
}