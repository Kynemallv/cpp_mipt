#include "vec2d.h"
#include <stdexcept>
#include <cmath>

double& Vec2d::operator[] (unsigned int index)
{
  switch (index)
  {
  case 0:
    return x;
  case 1:
    return y;
  default:
    throw std::out_of_range{
        "Vec2d: index out of range. It must be in [0;1]"};
  }
};

Vec2d operator+ (const Vec2d& v1, const Vec2d& v2)
{
  Vec2d result{};
  result += v1;
  result += v2;

  return result;
}

Vec2d operator- (const Vec2d& v1, const Vec2d& v2)
{
  Vec2d result{};
  result += v1;
  result -= v2;

  return result;
}

Vec2d operator* (const Vec2d& v, double a)
{
  Vec2d result{};
  result += v;
  result *= a;

  return result;
}

Vec2d operator/ (const Vec2d& v, double a)
{
  Vec2d result{};
  result += v;
  result /= a;

  return result;
}

double dot (const Vec2d& v1, const Vec2d& v2) {
  return v1.x*v2.x + v1.y*v2.y;
}

double cross (const Vec2d& v1, const Vec2d& v2) {
  return v1.x*v2.y - v2.x*v1.y;
}

double length (const Vec2d& vec) {
  return std::sqrt(dot(vec, vec));
}