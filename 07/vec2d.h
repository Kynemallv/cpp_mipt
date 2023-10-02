struct Vec2d
{
  double x{0}, y{0};
  Vec2d() = default;
  Vec2d(double xx, double yy) : x{xx}, y{yy} {};

  double& operator[] (unsigned int index);

  Vec2d& operator+= (const Vec2d& vec)
  {
    x += vec.x;
    y += vec.y;
    return *this;
  };

  Vec2d& operator-= (const Vec2d& vec)
  {
    x -= vec.x;
    y -= vec.y;
    return *this;
  };

  Vec2d& operator*= (double a)
  {
    x *= a;
    y *= a;
    return *this;
  };

  Vec2d& operator/= (double a)
  {
    x /= a;
    y /= a;
    return *this;
  };
};

Vec2d operator+ (const Vec2d& v1, const Vec2d& v2);
Vec2d operator- (const Vec2d& v1, const Vec2d& v2);
Vec2d operator* (const Vec2d& v, double a);
Vec2d operator/ (const Vec2d& v, double a);
double dot (const Vec2d& v1, const Vec2d& v2);
double cross (const Vec2d& v1, const Vec2d& v2);
double length (const Vec2d& vec);