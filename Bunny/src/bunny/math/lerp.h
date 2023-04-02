#pragma once
#include "vector.h"
namespace Bunny {
  namespace math {
    template<typename T>
    T lerp(T& from, T& to, bu_f32 progress) {
      return ((1.0f - progress) * from) + (progress * to);
    }
  }  // namespace math
}  // namespace Bunny