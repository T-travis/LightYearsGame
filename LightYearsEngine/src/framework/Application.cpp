#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace ly
{
  Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
    : mWindow{ sf::VideoMode(windowWidth, windowHeight), "Light Years", style },
    mTargetFramerate{ 60.f }, // 60 FPS target 
    mTickClock{},
    currentWorld{ nullptr },
    mCleanCycleClock{},
    mCleanCycleInterval{2.f}
  {

  }

  void Application::Run()
  {
    mTickClock.restart();
    float accumulatedTime = 0.f;
    // one second / target framerate = delta time (see notes)
    float targetDeltaTime = 1.f / mTargetFramerate;
    while (mWindow.isOpen())
    {
      sf::Event windowEvent;
      while (mWindow.pollEvent(windowEvent))
      {
        if (windowEvent.type == sf::Event::EventType::Closed)
        {
          mWindow.close();
        }
      }

      // Output the actual framerate just to show difference between targetDeltaTime
      //float frameDeltaTime = mTickClock.restart().asSeconds();
      //LOG("REAL ticking at framerate: %f", 1.f / frameDeltaTime);

      accumulatedTime += mTickClock.restart().asSeconds(); // restart & return ellapsed time
      while (accumulatedTime > targetDeltaTime)
      {
        accumulatedTime -= targetDeltaTime;
        TickInternal(targetDeltaTime);
        RenderInternal();
      }

    }
  }

  void Application::TickInternal(float deltaTime)
  {
    Tick( deltaTime);

    // World Tick after Application Tick
    if (currentWorld)
    {
      currentWorld->TickInternal(deltaTime);
    }

    // clean up unused assets
    if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
    {
      mCleanCycleClock.restart();
      AssetManager::Get().CleanCycle();
    }
  }

  void Application::Tick(float deltaTime)
  {

  }

  void Application::RenderInternal()
  {
    mWindow.clear();
    Render();
    mWindow.display();
  }

  void Application::Render()
  {
    if (currentWorld)
    {
      currentWorld->Render(mWindow);
    }
  }
}