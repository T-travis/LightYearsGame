#include "framework/MathUtility.h"

namespace  ly
{
  // used to convert degrees to radians 
  const float PI = 3.1415926535; 
  const float PI_RADIANS = 180.f; // PI Radians = 180 degrees

  // Deep explanation from Pikuma: https://www.youtube.com/watch?v=tEUpWgy-Tuo&t=129s
  sf::Vector2f RotationToVector(float rotation)
  {
    float radians = DegreesToRadians(rotation);
    return sf::Vector2f(std::cos(radians), std::sin(radians));
  }

  float DegreesToRadians(float degrees)
  {
    return degrees * (PI / PI_RADIANS);
  }

  float RadiansToDegrees(float radians)
  {
    return radians * (PI_RADIANS / PI);
  }
}