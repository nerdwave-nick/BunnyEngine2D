#pragma once
#include "bunny/application-event.h"
#include "bunny/event.h"
#include "bunny/imGui/imGuiLayer.h"
#include "bunny/layer-stack.h"
#include "bunny/timestep.h"
#include "bunny/window.h"

namespace bunny {
  class Application {
   public:
    Application(bu_str const& name = "bunny Application");
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

    ImGuiLayer* GetImGuiLayer() {
      return m_ImGuiLayer;
    }

    inline static Application& Get() {
      return *s_Instance;
    }
    inline Window& GetWindow() {
      return *m_Window;
    }

    void Close();

   private:
    bu_b OnWindowClosed(WindowCloseEvent& e);
    bu_b OnWindowResized(WindowResizedEvent& e);

   private:
    Scope<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bu_b m_Running   = true;
    bu_b m_Minimized = false;
    LayerStack m_LayerStack;

    f32 m_LastFrameTime;

   private:
    static Application* s_Instance;
  };

  // to be defined in client
  Application* CreateApplication();
}  // namespace bunny
