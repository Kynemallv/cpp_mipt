#include "vec2d.h"
#include <iostream>

int main ()
{
  Vec2d vec{3, 2};
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec[0] = 1;
  vec[1] = 2;
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec += Vec2d{1, 0};
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec -= Vec2d{1, 0};
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec *= 10;
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec /= 10;
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec = vec + Vec2d{1, 2};
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  vec = vec - Vec2d{1, 2};
  std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;

  std::cout << dot(vec, Vec2d{1, 2}) << std::endl;

  std::cout << cross(vec, Vec2d{2, 1}) << std::endl;

  std::cout << length(vec) << std::endl;
}