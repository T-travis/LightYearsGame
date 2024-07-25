#include "weapon/Shooter.h"

namespace ly
{
  void Shooter::Shoot()
  {
    if (CanShoot() && !IsOnCooldown())
    {
      // Call child class impl
      ShootImpl();
    }
  }

  Shooter::Shooter(Actor* owner)
    : mOwner{owner}
  {
    
  }
}