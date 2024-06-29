#include "framework/Application.h"
#include <iostream>

namespace ly
{
  Application::Application()
    : mWindow{ sf::VideoMode(1400, 1000), "Light Years" },
    mTargetFramerate{ 60.f }, // 60 FPS target 
    mTickClock{}
  {}

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
      //float frameDelteTime = mTickClock.restart().asSeconds();
      //std::cout << "REAL ticking at framerate: " << 1.f / frameDelteTime << std::endl;

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
    //std::cout << "ticking at framerate: " << 1.f / deltaTime << std::endl;
    Tick( deltaTime);
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
    sf::RectangleShape rect{ sf::Vector2f{100,100} };
    rect.setFillColor(sf::Color::Green);
    rect.setOrigin(50, 50);
    rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
    mWindow.draw(rect);
  }
}