#include "spaceship/SpaceShip.h"

namespace ly
{
  SpaceShip::SpaceShip(World* owningWorld, const std::string& texturePath)
    : Actor{ owningWorld, texturePath }, mVelocity{} {}

  void SpaceShip::Tick(float deltaTime)
  {
    Actor::Tick(deltaTime);
    AddActorLocationOffset(GetVelocity() * deltaTime);
  }

  void SpaceShip::SetVelocity(const sf::Vector2f& newVelocity)
  {
    mVelocity = newVelocity;
  }

  sf::Vector2f SpaceShip::GetVelocity() const { return mVelocity; }

  void SpaceShip::Shoot()
  {
  }

  void SpaceShip::BeginPlay()
  {
    Actor::BeginPlay();
    SetEnablePhysics(true);
  }


}