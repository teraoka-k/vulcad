#if !defined(VULCAD_DRAW_SHAPES_BEZIER)
#define VULCAD_DRAW_SHAPES_BEZIER

#include "point.cc"
#include <vector>

class Bezier {
public:
  Point origin, end;
  std::vector<Point> control;

  Bezier(std::vector<Point> points) {
    auto countPoints = points.size();
    for (int i = 0; i < countPoints; i++) {
      auto &point = points[i];
      if (i == 0)
        this->origin = point;
      else if (i == countPoints - 1)
        this->end = point;
      else
        this->control.push_back(point);
    }
  }
};

#endif // VULCAD_DRAW_SHAPES_BEZIER
