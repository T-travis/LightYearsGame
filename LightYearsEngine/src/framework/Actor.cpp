#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"
#include <box2d/b2_body.h>

namespace ly
{
  Actor::Actor(World* owningWorld, const std::string& texturePath)
    : mOwningWorld{ owningWorld }, 
      mHasBeganPlay{ false },
      mSprite{},
      mTexture{},
      mPhysicsBody{nullptr},
      mPhysicsEnabled{false}
  {
    SetTexture(texturePath);
  }

  void Actor::BeginPlayInternal()
  {
    if (!mHasBeganPlay)
    {
      mHasBeganPlay = true;
      BeginPlay();
    }
  }

  void Actor::BeginPlay()
  {
    //LOG("ACTOR begin play...");
  }

  void Actor::TickInternal(float deltaTime)
  {
    if (!IsPendingDestroy())
    {
      Tick(deltaTime);
    }
  }

  void Actor::Tick(float deltaTime)
  {
    //LOG("ACTOR tick...");
  }

  void Actor::SetTexture(const std::string& texturePath)
  {
    mTexture = AssetManager::Get().LoadTexture(texturePath);
    if (!mTexture) return;

    mSprite.setTexture(*mTexture);

    int textureWidth = mTexture->getSize().x;
    int textureHeight = mTexture->getSize().y;
    mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{ textureWidth, textureHeight } });
    CenterPivot();
  }

  void Actor::Render(sf::RenderWindow& window)
  {
    if (IsPendingDestroy()) return;

    window.draw(mSprite);
  }

  void Actor::SetActorLocation(const sf::Vector2f& newLocation)
  {
    mSprite.setPosition(newLocation);
    UpdatePhysicsBodyTransform();
  }

  void Actor::SetActorRotation(float newRotation)
  {
    mSprite.setRotation(newRotation);
    UpdatePhysicsBodyTransform();
  }

  void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
  {
    SetActorLocation(GetActorLocation() + offsetAmount);
  }

  void Actor::AddActorRotationOffset(float offsetAmount)
  {
    SetActorRotation(GetActorRotation() + offsetAmount);
  }

  sf::Vector2f Actor::GetActorLocation() const
  {
    return mSprite.getPosition();
  }

  float Actor::GetActorRotation() const
  {
    return mSprite.getRotation();
  }

  sf::Vector2f Actor::GetActorForwardDirection() const
  {
    return RotationToVector(GetActorRotation());
  }

  sf::Vector2f Actor::GetActorRightDirection() const
  {
    return RotationToVector(GetActorRotation() + 90.f);
  }

  sf::Vector2u Actor::GetWindowSize() const
  {
    return mOwningWorld->GetWindowSize();
  }

  sf::FloatRect Actor::GetActorGlobalBounds() const
  {
    return mSprite.getGlobalBounds();
  }

  bool Actor::IsActorOutOfWindowBounds() const
  {
    float windowWidth = GetWorld()->GetWindowSize().x;
    float windowHeight = GetWorld()->GetWindowSize().y;
    float actorWidth = GetActorGlobalBounds().width;
    float actorHeight = GetActorGlobalBounds().height;
    sf::Vector2f actorPosition = GetActorLocation();

    if (actorPosition.x < -actorWidth)
    {
      return true;
    }
    if (actorPosition.x > windowWidth + actorWidth)
    {
      return true;
    }
    if (actorPosition.y < -actorHeight)
    {
      return true;
    }
    if (actorPosition.y > windowHeight + actorHeight)
    {
      return true;
    }
    return false;
  }

  void Actor::SetEnablePhysics(bool enable)
  {
    mPhysicsEnabled = enable;
    if (mPhysicsEnabled)
    {
      InitializePhysics();
    }
    else
    {
      UnInitializePhysics();
    }
  }

  void Actor::OnActorBeginOverlap(Actor* other)
  {
    LOG("overlapped...");
  }

  void Actor::OnActorEndOverlap(Actor* other)
  {
    LOG("overlapp finised...");
  }

  void Actor::Destroy()
  {
    UnInitializePhysics();
    Object::Destroy();
  }

  void Actor::CenterPivot()
  {
    sf::FloatRect bound = mSprite.getGlobalBounds();
    mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
  }

  void Actor::InitializePhysics()
  {
    if (!mPhysicsBody)
    {
      mPhysicsBody = PhysicsSystem::Get().AddListener(this);
    }
  }

  void Actor::UnInitializePhysics()
  {
    if (mPhysicsBody)
    {
      PhysicsSystem::Get().RemoveListener(mPhysicsBody);
      mPhysicsBody = nullptr;
    }
  }

  void Actor::UpdatePhysicsBodyTransform()
  {
    if (mPhysicsBody)
    {
      float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
      b2Vec2 position{
        GetActorLocation().x * physicsScale,
        GetActorLocation().y * physicsScale
      };
      float rotation = DegreesToRadians(GetActorRotation());
      mPhysicsBody->SetTransform(position, rotation);
    }
  }

  Actor::~Actor()
  {
    LOG("ACTOR destroyed...");
  }
}
