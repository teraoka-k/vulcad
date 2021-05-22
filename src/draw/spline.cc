#if !defined(VULCAD_DRAW_SPLINE)
#define VULCAD_DRAW_SPLINE

#include "../math/matrix.cc"
#include "vec.cc"
#include <cmath>
#include <tuple>
#include <vector>

/** cubic curve described as a*x^2 + b*x^1 + c*x^0 */
struct cubicCurve {
  /** domain of x (e.g. `{1, 2}` for [1, 2], 1<=x<=2)*/
  std::tuple<float, float> domain;
  /** coefficient of x^3*/
  float x3;
  /** coefficient of x^2*/
  float x2;
  /** coefficient of x^1*/
  float x1;
  /** coefficient of x^0*/
  float x0;

  Vec getPointAt(float x) {
    return {x, x3 * x * x * x + x2 * x * x + x1 * x + x0};
  }
};

/** any curve that passess through any number of points */
class Spline {

public:
  /** spline is set of cubic curves that are connected smoothly*/
  std::vector<cubicCurve> curves;

  Spline(std::vector<Vec> points) {
    this->curves.resize(points.size() - 1);
    this->calculateCoefficients(points);
  }

  void draw() {}

private:
  /** basically 4 constraints for each curve, 4n constraints in total
      1. curve passes through the kth point
      2. curve passes through the k+1th point
      3. [[except the last curve]] derivative of the curve is equal to that of
     the next curve at the k+1th point
      4. [[except the last curve]] derivative of derivative of curve is equal
     to that of the next curve at the k+1th point
      5. [[only at the first or last curve]] derivative of derivative of curve
     is 0 at the first or last point */
  void calculateCoefficients(std::vector<Vec> points) {
    auto countCurves = this->curves.size();
    /** 4 coefficients (a, b, c, d) for each curve (ax^3 + bx^2 + cx + d) */
    auto countCoefficients = 4 * countCurves;
    /** solve coefficients of all the curves by linear equasion
     *  Ax = y
     *   A is 4n x 4n constraint matrix (n = len(curves))
     *   x is 4n coefficients vector (4 coefficients per curve) (n =
     * len(curves))
     *   y is right hand side vector
     */
    auto A = Mat(countCoefficients, countCoefficients);
    auto y = Mat(countCoefficients, 1);
    /** row index of constraint matrix A */
    int constraintIndex = 1;

    /**
     * if a curve passes through a point, then ax^3 + bx^2 + cx + d = y
     */
    auto curvePassThroughPoint =
        [&constraintIndex, &A, &y](Vec &point, int coefficientIndex) -> void {
      A._(constraintIndex, coefficientIndex) = point.x * point.x * point.x;
      A._(constraintIndex, coefficientIndex + 1) = point.x * point.x;
      A._(constraintIndex, coefficientIndex + 2) = point.x;
      A._(constraintIndex, coefficientIndex + 3) = 1;
      y._(constraintIndex, 1) = point.y;
      constraintIndex++;
    };

    /**
     * at the edge points, derivative of derivative 6ax + 2b = 0
     */
    auto curvatureIsZero = [&constraintIndex, &A,
                            &y](Vec &point, int coefficientIndex) -> void {
      A._(constraintIndex, coefficientIndex) = 6 * point.x;
      A._(constraintIndex, coefficientIndex + 1) = 2;
      y._(constraintIndex, 1) = 0;
      constraintIndex++;
    };

    for (int k = 0; k < countCurves; k++) {
      auto &curve = this->curves[k];
      auto pk = points[k];
      auto pk1 = points[k + 1];
      /** column index of coefficient a for a*x^3 in matrix A*/
      auto coefficientAkIndex = 4 * k + 1;
      auto coefficientAk1Index = 4 * (k + 1) + 1;
      // 1. curve passes through the kth point
      curvePassThroughPoint(pk, coefficientAkIndex);
      // 2. curve passes through the k+1th point
      curvePassThroughPoint(pk1, coefficientAkIndex);

      [[likely]] if (k != countCurves - 1) {
        /* 3. derivative is equal to that of the next curve
            thus (3ak*x^2 + 2bk*x + ck) - (3ak1*x^2 + 2bk*1x + ck1) = 0 */
        A._(constraintIndex, coefficientAkIndex) = 3 * pk1.x * pk1.x;
        A._(constraintIndex, coefficientAkIndex + 1) = 2 * pk1.x;
        A._(constraintIndex, coefficientAkIndex + 2) = 1;
        A._(constraintIndex, coefficientAk1Index) = -3 * pk1.x * pk1.x;
        A._(constraintIndex, coefficientAk1Index + 1) = -2 * pk1.x;
        A._(constraintIndex, coefficientAk1Index + 2) = -1;
        y._(constraintIndex, 1) = 0;
        constraintIndex++;

        /* 4. derivative of derivative is equal to that of the next curve
            thus (6ak*x + 2bk) - (6ak1x + 2bk1) = 0 */
        A._(constraintIndex, coefficientAkIndex) = 6 * pk1.x;
        A._(constraintIndex, coefficientAkIndex + 1) = 2;
        A._(constraintIndex, coefficientAk1Index) = -6 * pk1.x;
        A._(constraintIndex, coefficientAk1Index + 1) = -2;
        y._(constraintIndex, 1) = 0;
        constraintIndex++;
      }

      // 5. derivative of derivative is 0 at the first or last point
      [[unlikely]] if (k == 0) curvatureIsZero(pk, coefficientAkIndex);
      [[unlikely]] if (k == countCurves - 1)
          curvatureIsZero(pk1, coefficientAkIndex);
    }

    // solve linear equasion
    auto coefficients = A.inverse() * y;

    // set coefficients
    for (int k = 0; k < countCurves; k++) {
      auto &curve = this->curves[k];
      auto pk = points[k];
      auto pk1 = points[k + 1];
      curve.domain = std::make_tuple(pk.x, pk1.x);
      auto coefficientAIndex = 4 * k + 1;
      curve.x3 = coefficients._(coefficientAIndex, 1);
      curve.x2 = coefficients._(coefficientAIndex + 1, 1);
      curve.x1 = coefficients._(coefficientAIndex + 2, 1);
      curve.x0 = coefficients._(coefficientAIndex + 3, 1);
    }
  }
};

#endif // VULCAD_DRAW_SPLINE
