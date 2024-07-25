#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

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
    for (auto iter = mActors.begin(); iter != mActors.end();)
    {
      iter->get()->TickInternal(deltaTime);
      ++iter;
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

  sf::Vector2u World::GetWindowSize() const
  {
    return mOwningApp->GetWindowSize();
  }

  void World::CleanCycle()
  {
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
        ++iter;
      }
    }
  }

  void World::BeginPlay()
  {
    LOG("WORLD Began play...");
  }

  void World::Tick(float deltaTime)
  {
    //LOG("WORLD Tick at frame rate %f", 1.f / deltaTime);
  }
}