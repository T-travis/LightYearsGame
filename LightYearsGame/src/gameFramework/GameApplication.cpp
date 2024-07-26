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

    // test contact
    weak<SpaceShip> testSpaceShip = newWorld.lock()->SpawnActor<SpaceShip>();
    testSpaceShip.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
    testSpaceShip.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
    counter = 0.f;
  }

  void GameApplication::Tick(float deltaTime)
  {
    counter += deltaTime;
    if (counter > 10.f && !testPlayerSpaceShip.expired()) {
      testPlayerSpaceShip.lock()->Destroy();
    }
  }
}