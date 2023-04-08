#include "bupch.h"

#include "time.h"

#include <fmt/format.h>

/// @brief used to cut off time values at the nanosecond
static constexpr auto TIME_RESOLUTION_FACTOR = 1000000000;

namespace Bunny {
  Time Time::s_currentDelta = 1_s;
  bu_str Time::to_string() const {
    return fmt::format("[[Time]: {:.9f}]", m_seconds);
  }
  Time::Time(bu_f64 seconds) :
      m_seconds{
        trunc(seconds * TIME_RESOLUTION_FACTOR) / TIME_RESOLUTION_FACTOR} {}
}  // namespace Bunny