#include "player/PlayerSpaceShip.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"

namespace ly
{
  PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string& path)
    : SpaceShip{ owningWorld, path }, mMoveInput{}, mSpeed{200.f}
  {
  }

  void PlayerSpaceShip::Tick(float deltaTime)
  {
    SpaceShip::Tick(deltaTime);
    HandleInput();
    ConsumeInput(deltaTime);
  }

  void PlayerSpaceShip::SetSpeed(float newSpeed) { mSpeed = newSpeed; }

  float PlayerSpaceShip::GetSpeed() const { return mSpeed; }

  void PlayerSpaceShip::HandleInput()
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
      mMoveInput.y = -1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      mMoveInput.y = 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      mMoveInput.x = -1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      mMoveInput.x = 1.f;
    }

    NormalizeInput();
  }

  void PlayerSpaceShip::ConsumeInput(float deltaTime)
  {
    SetVelocity(mMoveInput * mSpeed);
    mMoveInput.x = mMoveInput.y = 0.f; // set back to not moving
  }

  void PlayerSpaceShip::NormalizeInput()
  {
    Normalize(mMoveInput);
  }
}