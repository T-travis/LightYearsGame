#pragma once
#include <SFML/Graphics.hpp>

// namespaces are good for: avoiding naming conflicts, organization, less identifiers
// in the global scopel, improve readability
namespace ly
{
  class Application
  {
  public:
    Application();
    void Run();
    
     
  private:
    void TickInternal(float deltaTime);
    virtual void Tick(float deltaTime);
    void RenderInternal();
    virtual void Render();


    sf::RenderWindow mWindow;
    float mTargetFramerate;
    sf::Clock mTickClock;
  };
}
