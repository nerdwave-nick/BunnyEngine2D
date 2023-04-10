#pragma once

#include "bunny/core/types.h"
#include "bunny/util/string-representable.interface.h"

namespace bunny {
  class KeyCode : public ToDebugString {
   public:
    enum Value {
      Space            = 32,
      Apostrophe       = 39,
      Comma            = 44,
      Minus            = 45,
      Period           = 46,
      Slash            = 47,
      Key0             = 48,
      Key1             = 49,
      Key2             = 50,
      Key3             = 51,
      Key4             = 52,
      Key5             = 53,
      Key6             = 54,
      Key7             = 55,
      Key8             = 56,
      Key9             = 57,
      Semicolon        = 59,
      Equal            = 61,
      A                = 65,
      B                = 66,
      C                = 67,
      D                = 68,
      E                = 69,
      F                = 70,
      G                = 71,
      H                = 72,
      I                = 73,
      J                = 74,
      K                = 75,
      L                = 76,
      M                = 77,
      N                = 78,
      O                = 79,
      P                = 80,
      Q                = 81,
      R                = 82,
      S                = 83,
      T                = 84,
      U                = 85,
      V                = 86,
      W                = 87,
      X                = 88,
      Y                = 89,
      Z                = 90,
      LeftBracket      = 91,
      Backslash        = 92,
      RightBracket     = 93,
      GraveAccent      = 96,
      World1           = 161,
      World2           = 162,
      Escape           = 256,
      Enter            = 257,
      Tab              = 258,
      Backspace        = 259,
      Insert           = 260,
      Delete           = 261,
      Right            = 262,
      Left             = 263,
      Down             = 264,
      Up               = 265,
      PageUp           = 266,
      PageDown         = 267,
      Home             = 268,
      End              = 269,
      CapsLock         = 280,
      ScrollLock       = 281,
      NumLock          = 282,
      PrintScreen      = 283,
      Pause            = 284,
      F1               = 290,
      F2               = 291,
      F3               = 292,
      F4               = 293,
      F5               = 294,
      F6               = 295,
      F7               = 296,
      F8               = 297,
      F9               = 298,
      F10              = 299,
      F11              = 300,
      F12              = 301,
      F13              = 302,
      F14              = 303,
      F15              = 304,
      F16              = 305,
      F17              = 306,
      F18              = 307,
      F19              = 308,
      F20              = 309,
      F21              = 310,
      F22              = 311,
      F23              = 312,
      F24              = 313,
      F25              = 314,
      Numblock0        = 320,
      Numblock1        = 321,
      Numblock2        = 322,
      Numblock3        = 323,
      Numblock4        = 324,
      Numblock5        = 325,
      Numblock6        = 326,
      Numblock7        = 327,
      Numblock8        = 328,
      Numblock9        = 329,
      NumblockDecimal  = 330,
      NumblockDivide   = 331,
      NumblockMultiply = 332,
      NumblockSubtract = 333,
      NumblockAdd      = 334,
      NumblockEnter    = 335,
      NumblockEqual    = 336,
      LeftShift        = 340,
      LeftCtrl         = 341,
      LeftAlt          = 342,
      LeftSuper        = 343,
      RightShift       = 344,
      RightCtrl        = 345,
      RightAlt         = 346,
      RightSuper       = 347,
      Menu             = 348,
    };

    KeyCode() = default;
    constexpr KeyCode(Value aButton) :
        value(aButton) {}

    explicit KeyCode(u32 aButton) :
        value((Value)aButton) {}

    // Allow switch and comparisons.
    constexpr operator Value() const {
      return value;
    }

    // Prevent usage: if(fruit)
    explicit operator bool() const = delete;

    constexpr bool operator==(KeyCode a) const {
      return value == a.value;
    }
    constexpr bool operator!=(KeyCode a) const {
      return value != a.value;
    }

    constexpr bool operator==(Value a) const {
      return value == a;
    }
    constexpr bool operator!=(Value a) const {
      return value != a;
    }

    constexpr bu_str to_debug_string() const override {
      switch (value) {
        case Space: return "[[KeyCode]: Space]";
        case Apostrophe: return "[[KeyCode]: Apostrophe]";
        case Comma: return "[[KeyCode]: Comma]";
        case Minus: return "[[KeyCode]: Minus]";
        case Period: return "[[KeyCode]: Period]";
        case Slash: return "[[KeyCode]: Slash]";
        case Key0: return "[[KeyCode]: Key0]";
        case Key1: return "[[KeyCode]: Key1]";
        case Key2: return "[[KeyCode]: Key2]";
        case Key3: return "[[KeyCode]: Key3]";
        case Key4: return "[[KeyCode]: Key4]";
        case Key5: return "[[KeyCode]: Key5]";
        case Key6: return "[[KeyCode]: Key6]";
        case Key7: return "[[KeyCode]: Key7]";
        case Key8: return "[[KeyCode]: Key8]";
        case Key9: return "[[KeyCode]: Key9]";
        case Semicolon: return "[[KeyCode]: Semicolon]";
        case Equal: return "[[KeyCode]: Equal]";
        case A: return "[[KeyCode]: A]";
        case B: return "[[KeyCode]: B]";
        case C: return "[[KeyCode]: C]";
        case D: return "[[KeyCode]: D]";
        case E: return "[[KeyCode]: E]";
        case F: return "[[KeyCode]: F]";
        case G: return "[[KeyCode]: G]";
        case H: return "[[KeyCode]: H]";
        case I: return "[[KeyCode]: I]";
        case J: return "[[KeyCode]: J]";
        case K: return "[[KeyCode]: K]";
        case L: return "[[KeyCode]: L]";
        case M: return "[[KeyCode]: M]";
        case N: return "[[KeyCode]: N]";
        case O: return "[[KeyCode]: O]";
        case P: return "[[KeyCode]: P]";
        case Q: return "[[KeyCode]: Q]";
        case R: return "[[KeyCode]: R]";
        case S: return "[[KeyCode]: S]";
        case T: return "[[KeyCode]: T]";
        case U: return "[[KeyCode]: U]";
        case V: return "[[KeyCode]: V]";
        case W: return "[[KeyCode]: W]";
        case X: return "[[KeyCode]: X]";
        case Y: return "[[KeyCode]: Y]";
        case Z: return "[[KeyCode]: Z]";
        case LeftBracket: return "[[KeyCode]: LeftBracket]";
        case Backslash: return "[[KeyCode]: Backslash]";
        case RightBracket: return "[[KeyCode]: RightBracket]";
        case GraveAccent: return "[[KeyCode]: GraveAccent]";
        case World1: return "[[KeyCode]: World1]";
        case World2: return "[[KeyCode]: World2]";
        case Escape: return "[[KeyCode]: Escape]";
        case Enter: return "[[KeyCode]: Enter]";
        case Tab: return "[[KeyCode]: Tab]";
        case Backspace: return "[[KeyCode]: Backspace]";
        case Insert: return "[[KeyCode]: Insert]";
        case Delete: return "[[KeyCode]: Delete]";
        case Right: return "[[KeyCode]: Right]";
        case Left: return "[[KeyCode]: Left]";
        case Down: return "[[KeyCode]: Down]";
        case Up: return "[[KeyCode]: Up]";
        case PageUp: return "[[KeyCode]: PageUp]";
        case PageDown: return "[[KeyCode]: PageDown]";
        case Home: return "[[KeyCode]: Home]";
        case End: return "[[KeyCode]: End]";
        case CapsLock: return "[[KeyCode]: CapsLock]";
        case ScrollLock: return "[[KeyCode]: ScrollLock]";
        case NumLock: return "[[KeyCode]: NumLock]";
        case PrintScreen: return "[[KeyCode]: PrintScreen]";
        case Pause: return "[[KeyCode]: Pause]";
        case F1: return "[[KeyCode]: F1]";
        case F2: return "[[KeyCode]: F2]";
        case F3: return "[[KeyCode]: F3]";
        case F4: return "[[KeyCode]: F4]";
        case F5: return "[[KeyCode]: F5]";
        case F6: return "[[KeyCode]: F6]";
        case F7: return "[[KeyCode]: F7]";
        case F8: return "[[KeyCode]: F8]";
        case F9: return "[[KeyCode]: F9]";
        case F10: return "[[KeyCode]: F10]";
        case F11: return "[[KeyCode]: F11]";
        case F12: return "[[KeyCode]: F12]";
        case F13: return "[[KeyCode]: F13]";
        case F14: return "[[KeyCode]: F14]";
        case F15: return "[[KeyCode]: F15]";
        case F16: return "[[KeyCode]: F16]";
        case F17: return "[[KeyCode]: F17]";
        case F18: return "[[KeyCode]: F18]";
        case F19: return "[[KeyCode]: F19]";
        case F20: return "[[KeyCode]: F20]";
        case F21: return "[[KeyCode]: F21]";
        case F22: return "[[KeyCode]: F22]";
        case F23: return "[[KeyCode]: F23]";
        case F24: return "[[KeyCode]: F24]";
        case F25: return "[[KeyCode]: F25]";
        case Numblock0: return "[[KeyCode]: Numblock0]";
        case Numblock1: return "[[KeyCode]: Numblock1]";
        case Numblock2: return "[[KeyCode]: Numblock2]";
        case Numblock3: return "[[KeyCode]: Numblock3]";
        case Numblock4: return "[[KeyCode]: Numblock4]";
        case Numblock5: return "[[KeyCode]: Numblock5]";
        case Numblock6: return "[[KeyCode]: Numblock6]";
        case Numblock7: return "[[KeyCode]: Numblock7]";
        case Numblock8: return "[[KeyCode]: Numblock8]";
        case Numblock9: return "[[KeyCode]: Numblock9]";
        case NumblockDecimal: return "[[KeyCode]: NumblockDecimal]";
        case NumblockDivide: return "[[KeyCode]: NumblockDivide]";
        case NumblockMultiply: return "[[KeyCode]: NumblockMultiply]";
        case NumblockSubtract: return "[[KeyCode]: NumblockSubtract]";
        case NumblockAdd: return "[[KeyCode]: NumblockAdd]";
        case NumblockEnter: return "[[KeyCode]: NumblockEnter]";
        case NumblockEqual: return "[[KeyCode]: NumblockEqual]";
        case LeftShift: return "[[KeyCode]: LeftShift]";
        case LeftCtrl: return "[[KeyCode]: LeftCtrl]";
        case LeftAlt: return "[[KeyCode]: LeftAlt]";
        case LeftSuper: return "[[KeyCode]: LeftSuper]";
        case RightShift: return "[[KeyCode]: RightShift]";
        case RightCtrl: return "[[KeyCode]: RightCtrl]";
        case RightAlt: return "[[KeyCode]: RightAlt]";
        case RightSuper: return "[[KeyCode]: RightSuper]";
        case Menu: return "[[KeyCode]: Menu]";
        default: return "[[KeyCode]: Invalid Keycode]";
      }
    }

   private:
    Value value;
  };
}  // namespace bunny
