#if !defined(VULCAD_TYPEDEF_APPPRIVATETYPES)
#define VULCAD_TYPEDEF_APPPRIVATETYPES

#include "draw/shapes/bezier.cc"
#include "draw/shapes/circle.cc"
#include "draw/shapes/line.cc"
#include "draw/shapes/point.cc"
#include "draw/shapes/spline.cc"
#include <cinttypes>
#include <variant>

struct Interval {
  float min = -1;
  float max = 1;

  float getDistance() { return max - min; }
};

struct CoordinatesRange {
  /** min x and max */
  Interval x;
  /** min y and max y*/
  Interval y;
  /** min z and max z*/
  Interval z;
};

/** color */
struct RGB {
  /** red (0~255) */
  int r;
  /** green (0~255) */
  int g;
  /** blue (0~255) */
  int b;
};

struct ScreenSize {
  uint16_t width;
  uint16_t height;
};

typedef std::variant<Point, Line, Circle, Bezier, Spline> Shape;

#endif // VULCAD_TYPEDEF_APPPRIVATETYPES
