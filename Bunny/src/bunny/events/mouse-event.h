#pragma once

#include "./event.h"

namespace Bunny {
  class MouseMovedEvent : public Event {
   public:
    MouseMovedEvent(bu_f32 x, bu_f32 y) :
        m_MouseX(x), m_MouseY(y) {}

    inline bu_f32 GetX() const {
      return m_MouseX;
    }
    inline bu_f32 GetY() const {
      return m_MouseY;
    }

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

   private:
    bu_f32 m_MouseX, m_MouseY;
  };

  class MouseScrolledEvent : public Event {
   public:
    MouseScrolledEvent(bu_f32 x, bu_f32 y) :
        m_XOffset(x), m_YOffset(y) {}

    inline bu_f32 GetXOffset() const {
      return m_XOffset;
    }
    inline bu_f32 GetYOffset() const {
      return m_YOffset;
    }

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

   private:
    bu_f32 m_XOffset, m_YOffset;
  };

  class MouseButtonEvent : public Event {
   public:
    inline MouseButton GetMouseButton() const {
      return m_Button;
    }
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
   protected:
    MouseButtonEvent(bu_i32 button) :
        m_Button(button) {}

    MouseButton m_Button;
  };

  class MouseButtonPressedEvent : public MouseButtonEvent {
   public:
    MouseButtonPressedEvent(bu_i32 button) :
        MouseButtonEvent(button) {}

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "[[MouseButtonPressedEvent]: " << m_Button.to_string() << "]";
      return ss.str();
    }
    EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  class MouseButtonReleasedEvent : public MouseButtonEvent {
   public:
    MouseButtonReleasedEvent(bu_i32 button) :
        MouseButtonEvent(button) {}

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "[[MouseButtonReleasedEvent]: " << m_Button.to_string() << "]";
      return ss.str();
    }
    EVENT_CLASS_TYPE(MouseButtonReleased)
  };
}  // namespace Bunny