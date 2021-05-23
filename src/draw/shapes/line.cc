#if !defined(VULCAD_DRAW_LINE)
#define VULCAD_DRAW_LINE

#include "point.cc"

class Line {
public:
  Point origin;
  Point end;

  Line(Point origin = {}, Point end = {1, 0}) {
    this->origin = origin;
    this->end = end;
  }
};

#endif // VULCAD_DRAW_LINE
