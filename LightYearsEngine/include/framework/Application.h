#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

// namespaces are good for: avoiding naming conflicts, organization, less identifiers
// in the global scopel, improve readability
namespace ly
{
  class World;
  class Application
  {
  public:
    Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
    void Run();
    sf::Vector2u GetWindowSize() const;
 
    // allows varios WorldTypes
    template<typename WorldType>
    weak<WorldType> LoadWorld()
    {
      // using weak pointer because the returning pointer doesn't need ownership

      shared<WorldType> newWorld{ new WorldType{this} };
      currentWorld = newWorld;
      currentWorld->BeginPlayInternal();
      return newWorld; // returning newWorld because it must return WorldType generic
    }
     
  private:
    void TickInternal(float deltaTime);
    virtual void Tick(float deltaTime);
    void RenderInternal();
    virtual void Render();


    sf::RenderWindow mWindow;
    float mTargetFramerate;
    sf::Clock mTickClock;

    shared<World> currentWorld;
    sf::Clock mCleanCycleClock;
    float mCleanCycleInterval;

  };
}
