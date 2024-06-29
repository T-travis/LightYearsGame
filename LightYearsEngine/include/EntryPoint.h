#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
  class Application; // forward declare
  
}

// extern means this needs to be implemented somewhere else like in our game
extern ly::Application* GetApplication();