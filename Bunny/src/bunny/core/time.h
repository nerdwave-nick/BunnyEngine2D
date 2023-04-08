#pragma once

#include "bunny/core/types.h"


namespace Bunny {

  /// @brief Represents time spans, time deltas and time steps with nanosecond resolution
  class Time {
   public:
    /// @brief constructs an instance of this class with the given time in seconds
    /// @param seconds the time in seconds this instance should represent
    explicit Time(bu_f64 seconds);

    /// @brief the time value represented by this instance in seconds
    /// @return the time in seconds as a double precision floating point value
    bu_f64 seconds() const {
      return m_seconds;
    }

    /// @brief the time value represented by this instance in milliseconds
    /// @return the time in milliseconds as a double precision floating point value
    bu_f64 milliseconds() const {
      return m_seconds * 1000.;
    }


    /// @brief the time value represented by this instance in microseconds
    /// @return the time in microseconds as a double precision floating point value
    bu_f64 microseconds() const {
      return m_seconds * 1000 * 1000;
    }

    /// @brief a formatted representation of this type
    /// @return a string of fixed 9 decimal precision, displaying the whole resolution of this type
    bu_str to_string() const;

   private:
    bu_f64 m_seconds;

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
    Time& operator*=(bu_f64 v) {
      m_seconds = m_seconds * v;
      return *this;
    }
    Time& operator/=(bu_f64 v) {
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
    friend Time operator*(Time a, bu_f64 b) {
      return Time(a.m_seconds * b);
    }
    friend Time operator*(bu_f64 b, Time a) {
      return Time(a.m_seconds * b);
    }
    friend Time operator/(Time a, bu_f64 b) {
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
}  // namespace Bunny


Bunny::Time inline operator"" _min(Bunny::bu_f64 f) {
  return Bunny::Time(f * 60);
}
Bunny::Time inline operator"" _min(Bunny::bu_u64 f) {
  return Bunny::Time(f * 60);
}

Bunny::Time inline operator"" _s(Bunny::bu_f64 f) {
  return Bunny::Time(f);
}
Bunny::Time inline operator"" _s(Bunny::bu_u64 f) {
  return Bunny::Time(f);
}

Bunny::Time inline operator"" _ms(Bunny::bu_f64 f) {
  return Bunny::Time(f / 1000.);
}
Bunny::Time inline operator"" _ms(Bunny::bu_u64 f) {
  return Bunny::Time(f / 1000.);
}

Bunny::Time inline operator"" _us(Bunny::bu_u64 f) {
  return Bunny::Time(f / 1000000.);
}
Bunny::Time inline operator"" _us(Bunny::bu_f64 f) {
  return Bunny::Time(f / 1000000.);
}

Bunny::Time inline operator"" _ns(Bunny::bu_u64 f) {
  return Bunny::Time(f / 1000000000.);
}

inline std::ostream& operator<<(std::ostream& os, const Bunny::Time& t) {
  os << t.to_string();
  return os;
}