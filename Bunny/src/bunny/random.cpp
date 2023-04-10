#include "bupch.h"

#include "Random.h"

#include <random>

namespace bunny {
  static std::mt19937 s_RandomEngine;
  static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
  void Random::Init() {
    s_RandomEngine.seed(std::random_device()());
  }

  f32 Random::Float() {
    return (f32)s_Distribution(s_RandomEngine) / (f32)std::numeric_limits<u32>::max();
  }
}  // namespace bunny
