#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
  class World; // World is the owner of the Actor
  class Actor : public Object
  {
  public:
    Actor(World* owningWorld, const std::string& texturePath = "");
    virtual ~Actor();
    void BeginPlayInternal();
    virtual void BeginPlay();
    void TickInternal(float deltaTime);
    virtual void Tick(float deltaTime);
    void SetTexture(const std::string& texturePath);
    void Render(sf::RenderWindow& window);
    void SetActorLocation(const sf::Vector2f& newLocation);
    void SetActorRotation(float newRotation);
    void AddActorLocationOffset(const sf::Vector2f& offsetAmount);
    void AddActorRotationOffset(float offsetAmount);
    sf::Vector2f GetActorLocation() const; // const because we are not modifying 
    float GetActorRotation() const;
    sf::Vector2f GetActorForwardDirection() const;
    sf::Vector2f GetActorRightDirection() const;
    sf::Vector2u GetWindowSize() const;

  private:
    World* mOwningWorld;
    bool mHasBeganPlay;
    
    sf::Sprite mSprite;
    shared<sf::Texture> mTexture;

    void CenterPivot();

  };
}