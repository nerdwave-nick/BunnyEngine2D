#pragma once

#include "bunny/typedefs.h"

namespace bunny {
  template<typename T>
  T lerp(T& from, T& to, f32 progress) {
    if (progress < 0)
      return from;
    else if (progress > 1)
      return to;
    return ((1.0f - progress) * from) + (progress * to);
  }
}  // namespace bunny
