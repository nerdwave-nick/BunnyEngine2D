#pragma once
#include "bupch.h"

#include "Bunny/core/typedefs.h"

namespace Bunny {

  enum class EventType {
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
  };

  enum EventCategory {
    None                     = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4),
  };

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const bu_ch* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual bu_i32 GetCategoryFlags() const override { return category; }

  class Event {
    friend class EventDispatcher;

   public:
    virtual EventType GetEventType() const  = 0;
    virtual const bu_ch* GetName() const    = 0;
    virtual bu_i32 GetCategoryFlags() const = 0;
    virtual bu_str ToString() const {
      return GetName();
    }

    inline bu_b IsInCategory(EventCategory category) {
      return GetCategoryFlags() & category;
    }
    bu_b Handled = false;

   protected:
  };

  class EventDispatcher {
   public:
    EventDispatcher(Event& event) :
        m_Event(event) {}

    template<typename T, typename F>
    bu_b Dispatch(const F& func) {
      if (m_Event.GetEventType() == T::GetStaticType()) {
        m_Event.Handled = func(static_cast<T&>(m_Event));
        return true;
      }
      return false;
    }

   private:
    Event& m_Event;
  };

  inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.ToString();
  }
}  // namespace Bunny