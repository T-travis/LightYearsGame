#pragma once
#include <string>

std::string GetResourceDir()
{
  // this runs before the code is compiled to set asset directory
#ifdef NDEBUG // release build
  return "assets/";
#else
  return"G:/LightYearsGameProject/LightYearsGame/assets/";
#endif
}
