#pragma once
#include "framework/Actor.h"
#include "framework/AssetManager.h"

namespace ly
{
  class SpaceShip : public Actor
  {
  public:
    SpaceShip(World* owningWorld, const std::string& texturePath = "");
    virtual void Tick(float deltaTime) override;
    void SetVelocity(const sf::Vector2f& newVelocity);
    sf::Vector2f GetVelocity() const;
    virtual void Shoot();

  private:
    sf::Vector2f mVelocity;
  };
}