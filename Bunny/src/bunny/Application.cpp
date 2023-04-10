#include "bupch.h"

#include "bunny/application.h"

#include <GLFW/glfw3.h>

#include "bunny/Renderer/Renderer.h"
#include "bunny/Renderer/Renderer2D.h"
#include "bunny/application-event.h"
namespace bunny {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


  Application* Application::s_Instance = nullptr;
  Application::Application(bu_str const& name) {
    BEGIN_PROFILING_SESSION("Blub");

    BU_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = Scope<Window>(Window::Create(WindowProperties(name)));
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    RenderCommand::Init();
    Renderer::Init();
    rendering::Renderer2D::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
  }

  Application::~Application() {
    END_PROFILING_SESSION();
    rendering::Renderer2D::Shutdown();
  }

  void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
    dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(Application::OnWindowResized));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
      (*--it)->OnEvent(e);
      if (e.Handled)
        break;
    }
  }

  void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* overlay) {
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
  }

  void Application::Close() {
    m_Running = false;
  }

  bu_b Application::OnWindowClosed(WindowCloseEvent& event) {
    m_Running = false;
    return true;
  }

  bu_b Application::OnWindowResized(WindowResizedEvent& e) {
    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
      m_Minimized = true;
      return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());

    return false;
  }

  void Application::Run() {
    PROFILE_FUNC();
    while (m_Running) {
      PROFILE_SCOPE("RUN loop");
      f32 time              = (f32)glfwGetTime();  // Platform::GetTime();
      Timestep timestep     = time - m_LastFrameTime;
      Timestep::s_DeltaTime = timestep;
      m_LastFrameTime       = time;
      if (!m_Minimized) {
        for (Layer* layer : m_LayerStack)
          layer->OnUpdate(timestep);
      }
      m_ImGuiLayer->Begin();
      for (Layer* layer : m_LayerStack)
        layer->OnImGuiRender();
      m_ImGuiLayer->End();
      m_Window->OnUpdate();  // 12
    }
  }
}  // namespace bunny
