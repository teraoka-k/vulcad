#if !defined(VULCAD_DRAW_POINT)
#define VULCAD_DRAW_POINT

#include "../../math/matrix.cc"
#include <vector>

class Point {
public:
  float x;
  float y;
  float z;

  Point(const Point &p) {
    x = p.x;
    y = p.y;
    z = p.z;
  }
  Point(float _x = .0f, float _y = .0f, float _z = .0f) {
    x = _x;
    y = _y;
    z = _z;
  }

  Point operator+(Point v) { return Point(x + v.x, y + v.y, z + v.z); }
  Point operator-(Point v) { return Point(x - v.x, y - v.y, z - v.z); }
  Point operator*(float scalar) {
    return Point(x * scalar, y * scalar, z * scalar);
  }
  friend Point operator*(float scalar, Point v) { return v * scalar; }
  Point operator/(float scalar) {
    return Point(x / scalar, y / scalar, z / scalar);
  }
  bool operator==(const Point v) { return x == v.x && y == v.y && z == v.z; };

  enum class Axis { x, y, z };
  /**
   * @param theta angle in radian
   * @param origin of rotation
   * @param axis around this axis
   */
  void rotate(float theta, Point origin = {0, 0, 0},
              Point::Axis axis = Point::Axis::z) {
    // relative coordinates around origin
    this->x -= origin.x;
    this->y -= origin.y;
    this->z -= origin.z;

    auto sin = std::sin(theta);
    auto cos = std::cos(theta);

    switch (axis) {
    case Point::Axis::x:
      this->y = cos * this->y - sin * this->z;
      this->z = sin * this->y + cos * this->z;
      break;
    case Point::Axis::y:
      this->z = cos * this->z - sin * this->x;
      this->x = sin * this->z + cos * this->x;
      break;
    case Point::Axis::z:
      this->x = cos * this->x - sin * this->y;
      this->y = sin * this->x + cos * this->y;
      break;
    }

    // original coordinates
    this->x += origin.x;
    this->y += origin.y;
    this->z += origin.z;
  }
};

#endif // VULCAD_DRAW_POINT