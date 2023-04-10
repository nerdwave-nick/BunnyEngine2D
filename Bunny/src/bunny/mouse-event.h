#pragma once

#include "./event.h"

namespace bunny {
  class MouseMovedEvent : public Event {
   public:
    MouseMovedEvent(f32 x, f32 y) :
        m_MouseX(x), m_MouseY(y) {}

    inline f32 GetX() const {
      return m_MouseX;
    }
    inline f32 GetY() const {
      return m_MouseY;
    }

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

   private:
    f32 m_MouseX, m_MouseY;
  };

  class MouseScrolledEvent : public Event {
   public:
    MouseScrolledEvent(f32 x, f32 y) :
        m_XOffset(x), m_YOffset(y) {}

    inline f32 GetXOffset() const {
      return m_XOffset;
    }
    inline f32 GetYOffset() const {
      return m_YOffset;
    }

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

   private:
    f32 m_XOffset, m_YOffset;
  };

  class MouseButtonEvent : public Event {
   public:
    inline MouseButton GetMouseButton() const {
      return m_Button;
    }
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
   protected:
    MouseButtonEvent(i32 button) :
        m_Button(button) {}

    MouseButton m_Button;
  };

  class MouseButtonPressedEvent : public MouseButtonEvent {
   public:
    MouseButtonPressedEvent(i32 button) :
        MouseButtonEvent(button) {}

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "[[MouseButtonPressedEvent]: " << m_Button.to_debug_string() << "]";
      return ss.str();
    }
    EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  class MouseButtonReleasedEvent : public MouseButtonEvent {
   public:
    MouseButtonReleasedEvent(i32 button) :
        MouseButtonEvent(button) {}

    bu_str to_debug_string() const override {
      bu_sstream ss;
      ss << "[[MouseButtonReleasedEvent]: " << m_Button.to_debug_string() << "]";
      return ss.str();
    }
    EVENT_CLASS_TYPE(MouseButtonReleased)
  };
}  // namespace bunny
