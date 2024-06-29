#include "gameFramework/GameApplication.h"
#include <iostream>

ly::Application* GetApplication()
{
  std::cout << "GetApplication.cpp GetApplication() called second..." << std::endl;

  return new ly::GameApplication{};
}

namespace ly
{
  
}