#if !defined(VULCAD_DRAW_CIRCLE)
#define VULCAD_DRAW_CIRCLE

#include "point.cc"
#include <math.h>

class Circle {
public:
  Point origin;
  float radius;

  Circle(Point origin = {}, float radius = 1) {
    this->origin = origin;
    this->radius = radius;
  }

  /**
   * @param theta angle in radian (x-axis is 0. anti clockwise)
   */
  Point getPointAt(float theta) {
    return this->origin + this->radius * Point{cos(theta), sin(theta)};
  }
};

#endif // VULCAD_DRAW_CIRCLE
