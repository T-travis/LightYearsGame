#include "gameFramework/GameApplication.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
  LOG("GetApplication.cpp GetApplication() called second...");

  return new ly::GameApplication{};
}

namespace ly
{
  GameApplication::GameApplication()
    : Application{980, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
  {
    weak<World> newWorld = LoadWorld<World>();
    newWorld.lock()->SpawnActor<Actor>();

    actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
    actorToDestroy.lock()->SetTexture("G:/LightYearsGameProject/LightYearsGame/assets/SpaceShooterRedux/PNG/playerShip1_blue.png");
    counter = 0;
  }

  void GameApplication::Tick(float deltaTime)
  {
    counter += deltaTime;
    if (counter > 2.f)
    {
      if (!actorToDestroy.expired())
      {
        actorToDestroy.lock()->Destroy();
      }
    }
  }
}