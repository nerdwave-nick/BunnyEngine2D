#include "bupch.h"

#include "bunny/time.h"

#include <fmt/format.h>

/// @brief used to cut off time values at the nanosecond
static constexpr auto TIME_RESOLUTION_FACTOR = 1000000000;

namespace bunny {
  Time Time::s_currentDelta = 1_s;
  bu_str Time::to_debug_string() const {
    return fmt::format("[Time({:.9f}s)]", m_seconds);
  }
  Time::Time(f64 seconds) :
      m_seconds{
        trunc(seconds * TIME_RESOLUTION_FACTOR) / TIME_RESOLUTION_FACTOR} {}
}  // namespace bunny
