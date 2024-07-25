#include "gameFramework/GameApplication.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"
#include "player/PlayerSpaceShip.h"
#include "framework/AssetManager.h"

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
    AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
    weak<World> newWorld = LoadWorld<World>();
    testPlayerSpaceShip = newWorld.lock()->SpawnActor<PlayerSpaceShip>();
    testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(490.f, 490.f));
    testPlayerSpaceShip.lock()->SetActorRotation(-90.f);

  }

  void GameApplication::Tick(float deltaTime)
  {

  }
}