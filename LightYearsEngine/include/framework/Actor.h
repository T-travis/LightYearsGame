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
    void BeginPlayInternal();
    virtual void BeginPlay();
    void TickInternal(float deltaTime);
    virtual void Tick(float deltaTime);
    void SetTexture(const std::string& texturePath);
    void Render(sf::RenderWindow& window);
    virtual ~Actor();

  private:
    World* mOwningWorld;
    bool mHasBeganPlay;
    
    sf::Sprite mSprite;
    shared<sf::Texture> mTexture;

  };
}