#pragma once

namespace ly
{
  class Actor;
  class Shooter
  {
  public:
    void Shoot();
    virtual bool CanShoot() const { return true; }
    virtual bool IsOnCooldown() const { return false; }
    Actor* GetOwner() const { return mOwner; }

  protected:
    Shooter(Actor* owner);

  private:
    Actor* mOwner;

    // This is a pure virtual function. 
    // This means, that subclasses have to implement this function.
    // If a class contains at least one pure virtual function, that makes 
    // the class "abstract", which means it cannot be instantiated.
    virtual void ShootImpl() = 0;


  };
}