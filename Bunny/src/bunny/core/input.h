#pragma once

#include "bunny/core/types.h"

namespace Bunny {
  class Input {
   public:
    static bu_b IsKeyPressed(bu_i32 keycode);

    static bu_b IsMouseButtonPressed(bu_i32 button);
    static bu_vec2 GetMousePosition();
    static bu_vec2 GetMousePositionRelative();
    static bu_f32 GetMouseX();
    static bu_f32 GetMouseY();
    static bu_f32 GetMouseXRelative();
    static bu_f32 GetMouseYRelative();
  };
}  // namespace Bunny