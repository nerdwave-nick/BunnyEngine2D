#pragma once
#include "bunny/events/event.h"

namespace bunny {
  class KeyEvent : public Event {
   public:
    inline KeyCode GetKeyCode() const {
      return m_KeyCode;
    }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

   protected:
    KeyEvent(i32 keycode) :
        KeyEvent((KeyCode)keycode) {}
    KeyEvent(KeyCode keycode) :
        m_KeyCode(keycode) {}

    KeyCode m_KeyCode;
  };

  class KeyPressedEvent : public KeyEvent {
   public:
    KeyPressedEvent(i32 keycode, i32 repeatcount) :
        KeyEvent(keycode), m_RepeatCount(repeatcount) {}

    inline i32 GetRepeatCount() const {
      return m_RepeatCount;
    }

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "[[KeyPressedEvent]: " << m_KeyCode.to_debug_string() << "(" << m_RepeatCount << " repeats)"
         << "]";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
   private:
    i32 m_RepeatCount;
  };

  class KeyReleasedEvent : public KeyEvent {
   public:
    KeyReleasedEvent(i32 keycode) :
        KeyEvent(keycode) {}

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "[[KeyReleasedEvent]: " << m_KeyCode.to_debug_string() << "]";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
  };

  class KeyTypedEvent : public KeyEvent {
   public:
    KeyTypedEvent(i32 keycode) :
        KeyEvent(keycode) {}

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "[[KeyTypedEvent]: " << m_KeyCode.to_debug_string() << "]";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
  };
}  // namespace bunny
