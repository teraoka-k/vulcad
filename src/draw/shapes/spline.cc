#if !defined(VULCAD_DRAW_SPLINE)
#define VULCAD_DRAW_SPLINE

#include "../../math/matrix.cc"
#include "point.cc"
#include <cmath>
#include <tuple>
#include <vector>

/**
 * https://en.wikipedia.org/wiki/Spline_interpolation
 * cubic curve in symmetrical form
 * f(x) = (1-t(x))y1 + t(x)y2 + t(x)(1-t(x)){(1-t(x))a+t(x)b}
 * where
 *  t(x) = (x-x1)/(x2-x1)
 *  a = f'(x1)(x2-x1) - (y2-y1)
 *  b = -f'(x2)(x2-x1) + (y2-y1)
 */
class CubicCurve {
public:
  /** (x1, y1) */
  Point origin;
  /** (x2, y2) */
  Point end;
  /** f'(x1) */
  float dfdx_origin;
  /** f'(x2) */
  float dfdx_end;

  /** f(x) = (1-t(x))y1 + t(x)y2 + t(x)(1-t(x)){(1-t(x))a+t(x)b}*/
  Point getPointAt(float x) {
    auto tx = this->t(x);
    auto a = this->a();
    auto b = this->b();
    auto y1 = this->origin.y;
    auto y2 = this->end.y;
    return {x,
            (1 - tx) * y1 + tx * y2 + tx * (1 - tx) * ((1 - tx) * a + tx * b)};
  }

private:
  /** a = f'(x1)(x2-x1) - (y2-y1) */
  float a() {
    auto distance = this->end - this->origin;
    return this->dfdx_origin * distance.x - distance.y;
  }
  /** b = -f'(x2)(x2-x1) + (y2-y1) */
  float b() {
    auto distance = this->end - this->origin;
    return -this->dfdx_end * distance.x + distance.y;
  }
  /** t(x) = (x-x1)/(x2-x1) */
  float t(float x) {
    return (x - this->origin.x) / (this->end.x - this->origin.x);
  }
};

/** any curve that passess through any number of points */
class Spline {

public:
  /** spline is set of cubic curves that are connected smoothly*/
  std::vector<CubicCurve> curves;
  std::vector<Point> points;

  Spline(std::vector<Point> points) {
    // store points only to export as dxf file
    this->points = points;
    this->curves.resize(points.size() - 1);
    this->calculateCoefficients(points);
  }

private:
  /** algorithm https://en.wikipedia.org/wiki/Spline_interpolation */
  void calculateCoefficients(std::vector<Point> points) {
    auto countPoints = this->points.size();
    auto A = Mat(countPoints, countPoints);
    auto y = Mat(countPoints, 1);

    // at the origin and end, curvature is zero
    auto d1 = this->points[1] - this->points[0];
    A._(1, 1) = 2.f / d1.x;
    A._(1, 2) = 1.f / d1.x;
    y._(1, 1) = 3 * d1.y / (d1.x * d1.x);
    auto dn = this->points[countPoints - 1] - this->points[countPoints - 2];
    A._(countPoints, countPoints - 1) = 1.f / dn.x;
    A._(countPoints, countPoints) = 2.f / dn.x;
    y._(countPoints, 1) = 3 * dn.y / (dn.x * dn.x);

    for (int k = 1; k < countPoints - 1; k++) {
      auto pPre = points[k - 1];
      auto p = points[k];
      auto pNext = points[k + 1];

      auto d1 = p - pPre;
      auto d2 = pNext - p;

      A._(k + 1, k) = 1.f / d1.x;
      A._(k + 1, k + 1) = 2 * (1.f / d1.x + 1.f / d2.x);
      A._(k + 1, k + 2) = 1.f / d2.x;
      y._(k + 1, 1) = 3 * (d1.y / (d1.x * d1.x) + d2.y / (d2.x * d2.x));
    }

    // solve linear equasion
    auto derivatives = A.inverse() * y;

    // define cubic curves
    for (int k = 0; k < this->curves.size(); k++) {
      auto &curve = this->curves[k];
      auto pk = points[k];
      auto pk1 = points[k + 1];
      curve.origin = pk;
      curve.end = pk1;
      curve.dfdx_origin = derivatives._(k + 1, 1);
      curve.dfdx_end = derivatives._(k + 2, 1);
    }
  }
};

#endif // VULCAD_DRAW_SPLINE
