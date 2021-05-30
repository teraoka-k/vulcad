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

  /** get length */
  float length() { return (end - origin).norm(); }

  /** get a point on this line by specifying distance from the line's end  */
  Point pointFromEnd(float length) {
    return this->end.to(this->origin, length);
  }

  /** get a point on this line by specifying distance from the line's origin  */
  Point pointFromOrigin(float length) {
    return this->origin.to(this->end, length);
  }
};

#endif // VULCAD_DRAW_LINE
