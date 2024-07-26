#pragma once
#include "framework/Actor.h"

namespace ly
{
  class Actor;
  class Bullet : public Actor
  {
  public:
    Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);
    void SetSpeed(float speed);
    float GetSpeed() const;
    void SetDamage(float damage);
    float GetDamage() const;
    virtual void Tick(float deltaTime) override;
    virtual void BeginPlay() override;

  private:
    Actor* mOwner;
    float mSpeed;
    float mDamage;

    void Move(float deltaTime);

  };
}