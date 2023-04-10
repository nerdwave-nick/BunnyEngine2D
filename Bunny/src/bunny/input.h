#pragma once

#include "bunny/core/types.h"
#include "bunny/input/key-codes.h"
#include "bunny/input/mouse-buttons.h"

namespace bunny {
  class Input {
   public:
    static bu_b is_key_pressed(KeyCode keycode);
    static bu_b is_mouse_button_pressed(MouseButton button);
    static bu_vec2 get_mouse_position();
    static bu_vec2 get_mouse_position_relative();
    static f32 get_mouse_x();
    static f32 get_mouse_y();
    static f32 get_mouse_x_relative();
    static f32 get_mouse_y_relative();
  };
}  // namespace bunny
