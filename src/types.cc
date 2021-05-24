#if !defined(VULCAD_TYPEDEF_APPPRIVATETYPES)
#define VULCAD_TYPEDEF_APPPRIVATETYPES

#include <cinttypes>

struct Interval {
  float min;
  float max;

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

struct ScreenSize {
  uint16_t width;
  uint16_t height;
};

#endif // VULCAD_TYPEDEF_APPPRIVATETYPES
