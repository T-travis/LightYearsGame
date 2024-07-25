#include "framework/PhysicsSystem.h"
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "framework/MathUtility.h"
#include "framework/Actor.h"

namespace ly
{
  unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

  PhysicsSystem& PhysicsSystem::Get()
  {
    if (!physicsSystem)
    {
      physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }
    return *physicsSystem;
  }

  void PhysicsSystem::Step(float deltaTime)
  {
    mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
  }

  b2Body* PhysicsSystem::AddListener(Actor* listener)
  {
    if (listener->IsPendingDestroy())
    {
      return nullptr;
    }
    
    // Setting pointer to listen to actor listener.  Actor is listener
    // for events from box2d like collisions.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
    // Set position of body to be the same as our listener.
    bodyDef.position.Set(
      listener->GetActorLocation().x * GetPhysicsScale(), 
      listener->GetActorLocation().y * GetPhysicsScale()
    );
    bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
    
    b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);
    b2PolygonShape shape;
    auto bound = listener->GetActorGlobalBounds();
    shape.SetAsBox(
      bound.width / 2.f * GetPhysicsScale(), 
      bound.height / 2.f * GetPhysicsScale()
    );

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);

    return body;
  }

  PhysicsSystem::PhysicsSystem()
    : mPhysicsWorld{ b2Vec2{0.f, 0.f} }, // set to 0 for no gravity
    mPhysicsScale{0.01f}, // lower scale of phycis to centimeters
    // documentation recommends 8 and 3
    mVelocityIterations{8},
    mPositionIterations{3}
  {
  }
}