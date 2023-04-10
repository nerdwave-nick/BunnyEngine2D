#pragma once

#include "bunny/constants.h"
#include "bunny/to-debug-string.h"
#include "bunny/typedefs.h"

#include <cmath>
#include <concepts>
#include <type_traits>


namespace bunny {
  namespace math {
    enum class AngleNormalization {
      ZeroToTwoPi    = 0,
      NegativePiToPi = 1
    };
    bunny::bu_str format_as_angle(bunny::f64 const value, bunny::f64 const degrees);
    bunny::bu_str format_as_angle(bunny::f32 const value, bunny::f32 const degrees);
    bunny::f64 inline constrainAngle(bunny::f64 x, AngleNormalization normalizationType) {
      switch (normalizationType) {
        case AngleNormalization::ZeroToTwoPi: {
          x = fmod(x, bunny::constants::TWO_PI);
          if (x < 0)
            x += bunny::constants::TWO_PI;
          return x;
        }
        case AngleNormalization::NegativePiToPi: {
          x = fmod(x + bunny::constants::PI, bunny::constants::TWO_PI);
          if (x < 0)
            x += bunny::constants::TWO_PI;
          return x - bunny::constants::PI;
        }
      }
    }
    bunny::f32 inline constrainAngle(bunny::f32 x, AngleNormalization normalizationType) {
      switch (normalizationType) {
        case AngleNormalization::ZeroToTwoPi: {
          x = fmodf(x, bunny::constants::TWO_PI);
          if (x < 0)
            x += bunny::constants::TWO_PI;
          return x;
        }
        case AngleNormalization::NegativePiToPi: {
          x = fmodf(x + bunny::constants::PI, bunny::constants::TWO_PI);
          if (x < 0)
            x += bunny::constants::TWO_PI;
          return x - bunny::constants::PI;
        }
      }
    }

    template<std::floating_point T>
    struct angle : public ToDebugString {
     private:
      T value_;
      explicit angle(T v) :
          value_{v} {}

     public:  // static functions
      static angle<T> from_deg(T v) {
        return angle<T>(v / 180. * constants::PI);
      }
      static angle<T> from_rad(T v) {
        return angle<T>(v);
      }

      template<std::floating_point S>
      static angle<T> asin(S val) {
        if constexpr (std::is_same_v<S, f32>)
          return angle<T>::from_rad(::asinf(val));
        else
          return angle<T>::from_rad(::asin(val));
      }
      template<std::floating_point S>
      static angle<T> acos(S val) {
        if constexpr (std::is_same_v<S, f32>)
          return angle<T>::from_rad(::acosf(val));
        else
          return angle<T>::from_rad(::acos(val));
      }
      template<std::floating_point S>
      static angle<T> atan(S val) {
        if constexpr (std::is_same_v<S, f32>)
          return angle<T>::from_rad(::atanf(val));
        else
          return angle<T>::from_rad(::atan(val));
      }
      template<std::floating_point S>
      static angle<T> asinh(S val) {
        if constexpr (std::is_same_v<S, f32>)
          return angle<T>::from_rad(::asinhf(val));
        else
          return angle<T>::from_rad(::asinh(val));
      }
      template<std::floating_point S>
      static angle<T> acosh(S val) {
        if constexpr (std::is_same_v<S, f32>)
          return angle<T>::from_rad(::acoshf(val));
        else
          return angle<T>::from_rad(::acosh(val));
      }
      template<std::floating_point S>
      static angle<T> atanh(S val) {
        if constexpr (std::is_same_v<S, f32>)
          return angle<T>::from_rad(::atanhf(val));
        else
          return angle<T>::from_rad(::atanh(val));
      }
      template<std::floating_point S>
      static angle<T> atan2(S val1, S val2) {
        if constexpr (!std::is_same_v<S, f32> && !std::is_same_v<T, f32>)
          return angle<T>::from_rad(::atan2(val1, val2));
        else
          return angle<T>::from_rad(::atan2f(val1, val2));
      }

     public:  // public methods
      bu_str to_debug_string() const override {
        return format_as_angle(value_, deg());
      }

      T deg() const {
        return value_ * 180. * constants::PI_INV;
      }
      T rad() const {
        return value_;
      }

      T sin() const {
        if constexpr (std::is_same_v<T, f32>)
          return ::sinf(value_);
        else
          return ::sin(value_);
      }
      T cos() const {
        if constexpr (std::is_same_v<T, f32>)
          return ::cosf(value_);
        else
          return ::cos(value_);
      }
      T tan() const {
        if constexpr (std::is_same_v<T, f32>)
          return ::tanf(value_);
        else
          return ::tan(value_);
      }
      T sinh() const {
        if constexpr (std::is_same_v<T, f32>)
          return ::sinhf(value_);
        else
          return ::sinh(value_);
      }
      T cosh() const {
        if constexpr (std::is_same_v<T, f32>)
          return ::coshf(value_);
        else
          return ::cosh(value_);
      }
      T tanh() const {
        if constexpr (std::is_same_v<T, f32>)
          return ::tanhf(value_);
        else
          return ::tanh(value_);
      }

      angle<T> normalize(AngleNormalization normalizationType = AngleNormalization::ZeroToTwoPi) {
        value_ = constrainAngle(value_, normalizationType);
        return *this;
      }

     public:  // operators
      angle<T>& operator+=(angle<T> v) {
        value_ += v.value_;
        return *this;
      }
      angle<T>& operator-=(angle<T> v) {
        value_ -= v.value_;
        return *this;
      }
      template<std::floating_point S>
      angle<T>& operator*=(S v) {
        value_ *= v;
        return *this;
      }
      template<std::floating_point S>
      angle<T>& operator/=(S v) {
        value_ /= v;
        return *this;
      }
      angle<T> operator-() {
        return angle<T>(-value_);
      }
      bool operator==(angle<T> b) {
        return value_ == b.value_;
      }
      bool operator!=(angle<T> b) {
        return value_ != b.value_;
      }
      bool operator>(angle<T> b) {
        return value_ > b.value_;
      }
      bool operator<(angle<T> b) {
        return value_ < b.value_;
      }
      bool operator<=(angle<T> b) {
        return value_ <= b.value_;
      }
      bool operator>=(angle<T> b) {
        return value_ >= b.value_;
      }

      template<std::floating_point S>
      operator angle<S>() {
        return angle<S>((S)value_);
      }

      friend angle<T> operator+(angle<T> a, angle<T> b) {
        return angle<T>(a.value_ + b.value_);
      }
      friend angle<T> operator-(angle<T> a, angle<T> b) {
        return angle<T>(a.value_ - b.value_);
      }
      template<std::floating_point S>
      friend angle<T> operator*(angle<T> a, S b) {
        return angle<T>(a.value_ * b);
      }
      template<std::floating_point S>
      friend angle<T> operator*(S b, angle<T> a) {
        return angle<T>(a.value_ * b);
      }
      template<std::floating_point S>
      friend angle<T> operator/(angle<T> a, S b) {
        return angle<T>(a.value_ / b);
      }
    };
  }  // namespace math
  using anglef32 = math::angle<f32>;
  using anglef64 = math::angle<f64>;
}  // namespace bunny


bunny::anglef32 inline operator"" _deg(long double f) {
  return bunny::anglef32::from_deg(f);
}
bunny::anglef32 inline operator"" _deg(unsigned long long int f) {
  return bunny::anglef32::from_deg(f);
}
bunny::anglef32 inline operator"" _rad(long double f) {
  return bunny::anglef32::from_rad(f);
}
bunny::anglef32 inline operator"" _rad(unsigned long long int f) {
  return bunny::anglef32::from_rad(f);
}
bunny::anglef32 inline operator"" _degf32(long double f) {
  return bunny::anglef32::from_deg(f);
}
bunny::anglef32 inline operator"" _degf32(unsigned long long int f) {
  return bunny::anglef32::from_deg(f);
}
bunny::anglef32 inline operator"" _radf32(long double f) {
  return bunny::anglef32::from_rad(f);
}
bunny::anglef32 inline operator"" _radf32(unsigned long long int f) {
  return bunny::anglef32::from_rad(f);
}
bunny::anglef64 inline operator"" _degf64(long double f) {
  return bunny::anglef64::from_deg(f);
}
bunny::anglef64 inline operator"" _degf64(unsigned long long int f) {
  return bunny::anglef64::from_deg(f);
}
bunny::anglef64 inline operator"" _radf64(long double f) {
  return bunny::anglef64::from_rad(f);
}
bunny::anglef64 inline operator"" _radf64(unsigned long long int f) {
  return bunny::anglef64::from_rad(f);
}
