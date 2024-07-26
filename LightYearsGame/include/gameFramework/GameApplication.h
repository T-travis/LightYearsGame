#pragma once
#include <framework/Application.h>
#include <framework/Core.h>
#include "spaceship/SpaceShip.h"

namespace ly
{
  class Actor;
  class PlayerSpaceShip;
  class GameApplication : public Application
  {
  public:
    GameApplication();

    virtual void Tick(float deltaTime) override;

  private:
    weak<PlayerSpaceShip> testPlayerSpaceShip;

    float counter;
  };
}