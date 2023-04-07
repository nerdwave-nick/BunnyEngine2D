#include "bupch.h"

#include "Random.h"

#include <random>

namespace Bunny {
  static std::mt19937 s_RandomEngine;
  static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
  void Random::Init() {
    s_RandomEngine.seed(std::random_device()());
  }

  bu_f32 Random::Float() {
    return (bu_f32)s_Distribution(s_RandomEngine) / (bu_f32)std::numeric_limits<bu_u32>::max();
  }
}  // namespace Bunny