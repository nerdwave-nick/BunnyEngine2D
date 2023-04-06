#pragma once
#include "./event.h"

namespace Bunny {

  class WindowCloseEvent : public Event {
   public:
    WindowCloseEvent() {}
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };

  class WindowResizedEvent : public Event {
   public:
    WindowResizedEvent(bu_u32 width, bu_u32 height) :
        m_Width(width), m_Height(height) {}
    inline bu_u32 GetWidth() const {
      return m_Width;
    }
    inline bu_u32 GetHeight() const {
      return m_Height;
    }

    bu_str ToString() const override {
      bu_sstream ss;
      ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
      return ss.str();
    }
    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);

   private:
    bu_u32 m_Width, m_Height;
  };

  class AppTickEvent : public Event {
    AppTickEvent() {}
    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };

  class AppUpdateEvent : public Event {
    AppUpdateEvent() {}
    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };


  class AppRenderEvent : public Event {
    AppRenderEvent() {}
    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };


}  // namespace Bunny