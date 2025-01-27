#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
  class Actor;
  class Application;
  class World
  {
  public:
    World(Application* owningApp);
    void BeginPlayInternal();
    void TickInternal(float deltaTime);
    void Render(sf::RenderWindow& window);
    virtual ~World();
    sf::Vector2u GetWindowSize() const;
    void CleanCycle();

    template<typename ActorType, typename... Args>
    weak<ActorType> SpawnActor(Args... args)
    {
      shared<ActorType> newActor{ new ActorType(this, args...) };
      mPendingActors.push_back(newActor);
      return newActor;
    }

  private:
    Application* mOwningApp;
    bool mBeganPlay;
    List<shared<Actor>> mActors;
    List<shared<Actor>> mPendingActors;

    void BeginPlay();
    void Tick(float deltaTime);
  };
}