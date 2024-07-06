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

  void AssetManager::CleanCycle()
  {
    for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
    {
      // check if asset isn't shared by any resource and thus isn't needed
      if (iter->second.unique())
      {
        LOG("cleaning assets 111111111111111111111111111111111111111...", iter->first.c_str());
        iter = mLoadedTextureMap.erase(iter);
      }
      else
      {
        ++iter;
      }
    }
  }

  AssetManager::AssetManager()
  {

  }
}
