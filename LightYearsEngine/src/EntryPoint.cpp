#include "EntryPoint.h"
#include "framework/Application.h"
#include "framework/Core.h"

// Our engine's main start location / entry point.
int main()
{
  LOG("EntryPoint.cpp main() called first...");

  // external -> called in GameApplication.cpp returning a GameApplication that inherits Application so we can call Run()
  ly::Application* app = GetApplication();
  app->Run();
  delete app;
}