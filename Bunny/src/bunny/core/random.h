#pragma once

#include "bunny/core/typedefs.h"

namespace Bunny {
  class Random {
   public:
    static void Init();
    static bu_f32 Float();
  };
}  // namespace Bunny