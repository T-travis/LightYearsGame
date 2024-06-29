#include "EntryPoint.h"
#include "framework/Application.h"
#include <iostream>

// Our engine's main start location / entry point.
int main()
{
  std::cout << "EntryPoint.cpp main() called first..." << std::endl;

  // external -> called in GameApplication.cpp returning a GameApplication that inherits Application so we can call Run()
  ly::Application* app = GetApplication();
  app->Run();
  delete app;
}