#pragma once
#include "./event.h"

namespace Bunny {
  class KeyEvent : public Event {
   public:
    inline bu_i32 GetKeyCode() const {
      return m_KeyCode;
    }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

   protected:
    KeyEvent(bu_i32 keycode) :
        m_KeyCode(keycode) {}

    bu_i32 m_KeyCode;
  };

  class KeyPressedEvent : public KeyEvent {
   public:
    KeyPressedEvent(bu_i32 keycode, bu_i32 repeatcount) :
        KeyEvent(keycode), m_RepeatCount(repeatcount) {}

    inline bu_i32 GetRepeatCount() const {
      return m_RepeatCount;
    }

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
   private:
    bu_i32 m_RepeatCount;
  };

  class KeyReleasedEvent : public KeyEvent {
   public:
    KeyReleasedEvent(bu_i32 keycode) :
        KeyEvent(keycode) {}

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "KeyReleasedEvent: " << m_KeyCode;
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
  };

  class KeyTypedEvent : public KeyEvent {
   public:
    KeyTypedEvent(bu_i32 keycode) :
        KeyEvent(keycode) {}

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "KeyTypedEvent: " << m_KeyCode;
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
  };
}  // namespace Bunny