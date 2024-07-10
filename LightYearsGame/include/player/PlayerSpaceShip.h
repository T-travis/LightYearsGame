#pragma once
#include "spaceship/SpaceShip.h"

namespace ly
{
  class PlayerSpaceShip : public SpaceShip
  {
  public:
    PlayerSpaceShip(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
    virtual void Tick(float deltaTime) override;
    void SetSpeed(float newSpeed);
    float GetSpeed() const;

  private:
    sf::Vector2f mMoveInput;
    float mSpeed;

    void HandleInput();
    void ConsumeInput(float deltaTime);
    // Clamp input to produce consistent speed
    void NormalizeInput();

  };
}