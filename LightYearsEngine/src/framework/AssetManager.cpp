#include "framework/AssetManager.h"

namespace ly
{
  // init staic variable:
  unique<AssetManager> AssetManager::assetManager{ nullptr };

  shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
  {
    auto found = mLoadedTextureMap.find(path);
    // return preloaded asset
    if (found != mLoadedTextureMap.end())
    {
      // second is the value in key value dictionary
      return found->second;
    }
    
    // load asset from file and save in dictionary
    shared<sf::Texture> newTexture{ new sf::Texture };
    if (newTexture->loadFromFile(path))
    {
      mLoadedTextureMap.insert({ path, newTexture });
      return newTexture;
    }

    // nothing preloaded and path couldn't be found
    return shared<sf::Texture> {nullptr};
  }

  AssetManager& AssetManager::Get()
  {
    if (!assetManager)
    {
      assetManager = unique<AssetManager>{new AssetManager};
    }

    return *assetManager;
  }

  AssetManager::AssetManager()
  {

  }
}
