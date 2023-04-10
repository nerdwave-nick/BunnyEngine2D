#pragma once

#include "bunny/to-debug-string.h"
#include "bunny/types.h"

namespace bunny {

  /// @brief Represents time spans, time deltas and time steps with nanosecond resolution
  class Time : public ToDebugString {
   public:
    /// @brief constructs an instance of this class with the given time in seconds
    /// @param seconds the time in seconds this instance should represent
    explicit Time(f64 seconds);

    /// @brief the time value represented by this instance in seconds
    /// @return the time in seconds as a double precision floating point value
    f64 seconds() const {
      return m_seconds;
    }

    /// @brief the time value represented by this instance in milliseconds
    /// @return the time in milliseconds as a double precision floating point value
    f64 milliseconds() const {
      return m_seconds * 1000.;
    }


    /// @brief the time value represented by this instance in microseconds
    /// @return the time in microseconds as a double precision floating point value
    f64 microseconds() const {
      return m_seconds * 1000 * 1000;
    }

    /// @brief a formatted representation of this type
    /// @return a string of fixed 9 decimal precision, displaying the whole resolution of this type
    bu_str to_debug_string() const override;

   private:
    f64 m_seconds;

   public:
    /// @brief an ease of use accessor to access the delta time of the last frame
    /// @return the delta time of the last frame
    static Time const current_delta() {
      return s_currentDelta;
    }

   private:
    static Time s_currentDelta;

   public:
    Time& operator+=(Time v) {
      m_seconds += v.m_seconds;
      return *this;
    }
    Time& operator-=(Time v) {
      m_seconds -= v.m_seconds;
      return *this;
    }
    Time& operator*=(f64 v) {
      m_seconds = m_seconds * v;
      return *this;
    }
    Time& operator/=(f64 v) {
      m_seconds = Time(m_seconds / v).m_seconds;
      return *this;
    }


    Time operator-() {
      return Time(-m_seconds);
    }
    friend Time operator+(Time a, Time b) {
      return Time(a.m_seconds + b.m_seconds);
    }
    friend Time operator-(Time a, Time b) {
      return Time(a.m_seconds - b.m_seconds);
    }
    friend Time operator*(Time a, f64 b) {
      return Time(a.m_seconds * b);
    }
    friend Time operator*(f64 b, Time a) {
      return Time(a.m_seconds * b);
    }
    friend Time operator/(Time a, f64 b) {
      return Time(a.m_seconds / b);
    }

    bool operator==(Time b) {
      return m_seconds == b.m_seconds;
    }
    bool operator!=(Time b) {
      return m_seconds != b.m_seconds;
    }
    bool operator>(Time b) {
      return m_seconds > b.m_seconds;
    }
    bool operator<(Time b) {
      return m_seconds < b.m_seconds;
    }
    bool operator<=(Time b) {
      return m_seconds <= b.m_seconds;
    }
    bool operator>=(Time b) {
      return m_seconds >= b.m_seconds;
    }
  };
}  // namespace bunny


bunny::Time inline operator"" _min(bunny::f64 f) {
  return bunny::Time(f * 60);
}
bunny::Time inline operator"" _min(bunny::u64 f) {
  return bunny::Time(f * 60);
}

bunny::Time inline operator"" _s(bunny::f64 f) {
  return bunny::Time(f);
}
bunny::Time inline operator"" _s(bunny::u64 f) {
  return bunny::Time(f);
}

bunny::Time inline operator"" _ms(bunny::f64 f) {
  return bunny::Time(f / 1000.);
}
bunny::Time inline operator"" _ms(bunny::u64 f) {
  return bunny::Time(f / 1000.);
}

bunny::Time inline operator"" _us(bunny::u64 f) {
  return bunny::Time(f / 1000000.);
}
bunny::Time inline operator"" _us(bunny::f64 f) {
  return bunny::Time(f / 1000000.);
}

bunny::Time inline operator"" _ns(bunny::u64 f) {
  return bunny::Time(f / 1000000000.);
}
