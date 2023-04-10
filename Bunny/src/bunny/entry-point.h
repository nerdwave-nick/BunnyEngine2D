#pragma once

#ifdef BU_PLATFORM_WINDOWS

extern bunny::Application* bunny::CreateApplication();

int main(int argc, char** argv) {
  bunny::Log::Init();
  auto app = bunny::CreateApplication();
  app->Run();
  delete app;
}

#endif