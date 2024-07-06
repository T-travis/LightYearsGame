#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly
{
  class AssetManager
  {
  public:
    shared<sf::Texture> LoadTexture(const std::string& path);
    static AssetManager& Get();

  // derived classes can use things in protected
  protected: 
    // being protected a child class can call this constructor and no longer
    // and not use the Singleton Patter if not desired
    AssetManager();

  private:
    // Singleton Pattern is used to not load assets more than once.
    // Enforced by using static so all instances share the same value
    // and using a Unique Pointer that can't be copied/transfered.
    static unique<AssetManager> assetManager;

    Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
  };
}