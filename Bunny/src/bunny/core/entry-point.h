#pragma once

#ifdef BU_PLATFORM_WINDOWS

extern Bunny::Application* Bunny::CreateApplication();

int main(int argc, char** argv) {
  Bunny::Log::Init();
  auto app = Bunny::CreateApplication();
  app->Run();
  delete app;
}

#endif