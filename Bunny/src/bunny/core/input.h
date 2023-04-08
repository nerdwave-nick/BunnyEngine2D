#pragma once

#include "bunny/core/key-codes.h"
#include "bunny/core/mouse-buttons.h"
#include "bunny/core/types.h"

namespace Bunny {
  class Input {
   public:
    static bu_b is_key_pressed(KeyCode keycode);
    static bu_b is_mouse_button_pressed(MouseButton button);
    static bu_vec2 get_mouse_position();
    static bu_vec2 get_mouse_position_relative();
    static bu_f32 get_mouse_x();
    static bu_f32 get_mouse_y();
    static bu_f32 get_mouse_x_relative();
    static bu_f32 get_mouse_y_relative();
  };
}  // namespace Bunny