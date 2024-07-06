#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
  World::World(Application* owningApp)
    : mOwningApp{owningApp}, 
      mBeganPlay{false},
      mActors{},
      mPendingActors{}
  {

  }

  void World::BeginPlayInternal()
  {
    if (!mBeganPlay)
    {
      mBeganPlay = true;
      BeginPlay();
    }
  }

  void World::TickInternal(float deltaTime)
  {
    // move mPendingActors to mActors
    for (shared<Actor> actor : mPendingActors)
    {
      mActors.push_back(actor);
      actor->BeginPlay(); // begin new actors
    }
    mPendingActors.clear(); // clear temp actors
    // Every World tick, we Tick each Actor
    // using iterator instead of loop above
    // iterators are good for when removing from a list you're iterating over
    for (auto iter = mActors.begin(); iter != mActors.end();)
    {
      if (iter->get()->IsPendingDestroy())
      {
        // NOTE: is a bigger game it would be better to have a timer that when runs
        // out clears Actors and other objects ready to be destroyed.
        iter = mActors.erase(iter); // remove from list to destroy Actor
      }
      else
      {
        iter->get()->TickInternal(deltaTime);
        ++iter;
      }
    }
    
    Tick(deltaTime);
  }

  void World::Render(sf::RenderWindow& window)
  {
    for (auto& actor : mActors)
    {
      actor->Render(window);
    }
  }

  World::~World()
  {

  }

  void World::BeginPlay()
  {
    LOG("WORLD Began play...");
  }

  void World::Tick(float deltaTime)
  {
    LOG("WORLD Tick at frame rate %f", 1.f / deltaTime);
  }
}