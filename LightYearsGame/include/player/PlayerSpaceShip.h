#pragma once
#include "spaceship/SpaceShip.h"


namespace ly
{
  class BulletShooter;
  class PlayerSpaceShip : public SpaceShip
  {
  public:
    PlayerSpaceShip(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
    virtual void Tick(float deltaTime) override;
    void SetSpeed(float newSpeed);
    float GetSpeed() const;
    virtual void Shoot() override;

  private:
    sf::Vector2f mMoveInput;
    float mSpeed;
    unique<BulletShooter> mShooter;

    void HandleInput();
    void ConsumeInput(float deltaTime);
    // Keep input at consistent speed.
    void NormalizeInput();
    // Keep input within screen.
    void ClampInputOnEdge();

  };
}