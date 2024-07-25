#include "player/PlayerSpaceShip.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "framework/Core.h"
#include "weapon/BulletShooter.h"

namespace ly
{
  PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string& path)
    : SpaceShip{ owningWorld, path }, 
    mMoveInput{}, 
    mSpeed{200.f},
    mShooter{new BulletShooter{this, 0.1f}}
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

  void PlayerSpaceShip::Shoot()
  {
    if (mShooter)
    {
      mShooter->Shoot();
    }
  }

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

    ClampInputOnEdge();
    NormalizeInput();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      Shoot();
    }
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

  void PlayerSpaceShip::ClampInputOnEdge()
  {
    sf::Vector2f actorLocation = GetActorLocation();

    // check left edge
    if (actorLocation.x < 0 && mMoveInput.x == -1.f)
    {
      mMoveInput.x = 0.f;
    }

    // check right edge
    if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
    {
      mMoveInput.x = 0.f;
    }

    // check top edge
    if (actorLocation.y < 0 && mMoveInput.y == -1.f)
    {
      mMoveInput.y = 0.f;
    }

    // check bottom edge
    if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
    {
      mMoveInput.y = 0.f;
    }

    
  }
}