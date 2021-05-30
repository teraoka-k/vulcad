#if !defined(VULCAD_DRAW_POINT)
#define VULCAD_DRAW_POINT

#include "../../math/matrix.cc"
#include <math.h>
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

  /**
   * get point p3 between this point p1 and another p2
   * such that (p1-p3) : (p3-p2) = t : 1-t
   */
  Point between(Point another, float t) {
    return (1 - t) * Point(x, y, z) + t * another;
  }

  /**
   * get middle point between this point and another
   */
  Point middle(Point another) { return this->between(another, 1.f / 2.f); }

  /** regard point as vector and get length */
  float norm() { return sqrt(x * x + y * y + z * z); }

  /** regard point as vector and get normalized vector */
  Point normalize() { return Point(x, y, z) / this->norm(); }

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

  /** create a new point relative to this point */
  Point to(float dx = 0, float dy = 0, float dz = 0) {
    return {x + dx, y + dy, z + dz};
  }
  /** create a new point relative to this point towards another point*/
  Point to(Point towards, float length) {
    auto dVec =
        Point(towards.x - x, towards.y - y, towards.z - z).normalize() * length;
    return this->to(dVec.x, dVec.y, dVec.z);
  }
  /**
   * create a new point relative to this point in angular coodinates
   * @param theta angle in degree. x-axis is zero and counter clockwise is
   * positive
   * @param length
   * @param axis theta is defined in xy plane by default, i.e. around z-axis
   * */
  Point toInAngular(float theta = 0, float length = 0,
                    Point::Axis axis = Point::Axis::z) {

    auto thetaRadian = (float)M_PI / 180.f * theta;
    auto d1 = length * cos(thetaRadian);
    auto d2 = length * sin(thetaRadian);
    switch (axis) {
    case Point::Axis::x:
      return {x, y + d1, z + d2};
    case Point::Axis::y:
      return {x + d2, y, z + d1};
    default:
      return {x + d1, y + d2, z};
    }
  }
};

#endif // VULCAD_DRAW_POINT