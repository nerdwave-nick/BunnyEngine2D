#pragma once
#include "bunny/core/types.h"
#include "bunny/util/string-representable.interface.h"
namespace bunny {
  /// @brief enum-like representation of mouse buttons
  class MouseButton : public ToDebugString {
   public:
    /// @brief  the underlying enum
    enum Value {
      Button1    = 0,
      Button2    = 1,
      Button3    = 2,
      Button4    = 3,
      Button5    = 4,
      Button6    = 5,
      Button7    = 6,
      Button8    = 7,
      ButtonLast = 8,
      Left       = 0,
      Right      = 1,
      Middle     = 2
    };

    MouseButton() = default;
    constexpr MouseButton(Value aButton) :
        value(aButton) {}

    explicit MouseButton(u32 aButton) :
        value((Value)aButton) {}

    /// @brief Allow switch and comparisons.
    constexpr operator Value() const {
      return value;
    }

    /// @brief Prevent usage: if(fruit)
    explicit operator bool() const = delete;

    constexpr bool operator==(MouseButton a) const {
      return value == a.value;
    }
    constexpr bool operator!=(MouseButton a) const {
      return value != a.value;
    }

    constexpr bool operator==(Value a) const {
      return value == a;
    }
    constexpr bool operator!=(Value a) const {
      return value != a;
    }

    /// @brief debug string representation
    constexpr bu_str to_debug_string() const override {
      switch (value) {
        case Left: return "[[MouseButton]: Left/Button1]";
        case Right: return "[[MouseButton]: Right/Button2]";
        case Middle: return "[[MouseButton]: Middle/Button3]";
        case Button4: return "[[MouseButton]: Button4]";
        case Button5: return "[[MouseButton]: Button5]";
        case Button6: return "[[MouseButton]: Button6]";
        case Button7: return "[[MouseButton]: Button7]";
        case Button8: return "[[MouseButton]: Button8]";
        default: return "[[Invalid Mouse Button]]";
      }
    }

   private:
    Value value;
  };
}  // namespace bunny
