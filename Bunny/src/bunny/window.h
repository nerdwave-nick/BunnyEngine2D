#pragma once
#include "bupch.h"

#include "bunny/Core/Core.h"
#include "bunny/Events/Event.h"

namespace bunny {
  struct WindowProperties {
    bu_str Title;
    u32 Width;
    u32 Height;

    WindowProperties(const bu_str& title = "bunny Engine",
                     u32 width           = 1280,
                     u32 height          = 720) :
        Title(title),
        Width(width), Height(height) {}
  };

  // Interface representing a desktop system based Window
  class Window {
   public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;

    virtual u32 GetWidth() const  = 0;
    virtual u32 GetHeight() const = 0;

    // Window attributes
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bu_b enabled)                            = 0;
    virtual bu_b IsVSync() const                                   = 0;

    virtual void* GetNativeWindow() const = 0;

    static Window* Create(const WindowProperties& props = WindowProperties());
  };
}  // namespace bunny
