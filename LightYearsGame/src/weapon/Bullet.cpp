#include "weapon/Bullet.h"

namespace ly
{
  Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
    : Actor{ world, texturePath },
    mOwner{ owner },
    mSpeed{ speed },
    mDamage{ damage }
  {
  }

  void Bullet::SetSpeed(float speed)
  {
    mSpeed = speed;
  }

  float Bullet::GetSpeed() const
  {
    return mSpeed;
  }

  void Bullet::SetDamage(float damage)
  {
    mDamage = damage;
  }

  float Bullet::GetDamage() const
  {
    return mDamage;
  }

  void Bullet::Tick(float deltaTime)
  {
    Actor::Tick(deltaTime);
    Move(deltaTime);

    // Clean up bullet assets when out of bounds.
    if (IsActorOutOfWindowBounds())
    {
      Destroy();
    }
  }

  void Bullet::Move(float deltaTime)
  {
    AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
  }


}