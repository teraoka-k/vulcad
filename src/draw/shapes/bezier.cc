#if !defined(VULCAD_DRAW_SHAPES_BEZIER)
#define VULCAD_DRAW_SHAPES_BEZIER

#include "../../math/binomial.cc"
#include "../../math/matrix.cc"
#include "point.cc"
#include <vector>

/**
 * general bezier curve that accespts any number of points
 * defined by fit points, not control points
 */
class Bezier {
public:
  std::vector<Point> points;

  /** points to pass through, and parameter t for each point*/
  Bezier(std::vector<Point> points, std::vector<float> t = {}) {
    this->calculateControlPoints(points, t);
  }

  Point end() { return this->points[this->points.size() - 1]; }

  /** get point by parameter t (0<=t<=1)*/
  Point getPointAt(float t) {
    /** number of points */
    auto n = this->points.size();
    /*  p = Sigma { (1-t)^(n-1-k) t^k n-1Ck pk } (k=0, ..., n-1) */
    return sigmaVector(
        [n, t, this](int k) {
          return (pow(1 - t, n - 1 - k) * pow(t, k) * binomial(n - 1, k)) *
                 this->points[k];
        },
        0, n - 1);
  }

  Point origin() { return this->points[0]; }

private:
  /** calculate control points from the points that the curve passes through  */
  void calculateControlPoints(std::vector<Point> points, std::vector<float> t) {
    /*
    "algorithm to solve control points c1 to cn-2"
       each ck (k=1, ..., n-2) is defined by 2 variables xk and yk;
       thus,  Let c be vector of size 2(n-2) whose elemetns are {x1, y1, x2, y2,
    ... , xn-2, yn-2}; and Let A be constraint matrix size 2(n-2) by 2(n-2); and
    Let b be vector of size 2(n-2) whose elemetns are expected values for each
      constraints;

     Because bezier curve passes through the points p1, ..., pn-2,
     if t1,...,tn-2 are known,
     then bezer satisfies 2(n-2) conditions as following,
      p1 = Sigma { (1-t1)^(n-1-k) * t1^k n-1Ck fk }
       ...
      pn-2 = Sigma { (1-t)^(n-1-k) * t^k n-1Ck fk }
      (k=0, ..., n-1, fk = p0 or c1,...,cn-2, or pn-1)

      which is equal to the following conditions
        p1 -p0 -pn-1 = Sigma { (1-t1)^(n-1-k) * t1^k n-1Ck pk }
         ...
        pn-2 -p0 -pn-1 = Sigma { (1-t)^(n-1-k) * t^k n-1Ck pk }
        (k=1, ..., n-2)

    this filles all the rows of constraint matrix A and
    all the elements of the vector b,
    and control points are solved by a linear equasion A c = b
    thus,  c = A^-1 * b; */

    /** number of points (p0, ..., pn-1)*/
    auto n = points.size();

    // set default value to t
    if (t.size() == 0) {
      auto dt = 1.f / (float)(n - 1);
      for (int i = 0; i < n; i++)
        t.push_back(dt * i < 1 ? dt * i : 1);
    }

    /** expected values (Ac = b) */
    auto b = Mat(2 * (n - 2), 1);
    /** constraints (Ac = b) */
    auto A = Mat(2 * (n - 2), 2 * (n - 2));

    /*
    curve passes through points p1, ..., pn-2,
     implying that
       pi -(1-t)^(n-1) p0 - t^(n-1) pn-1
     is equal to
       Sigma { (1-ti)^(n-1-k) * ti^k n-1Ck pk }
     for
       k = 1, 2, ..., n-2
    */
    auto p0 = points[0], pn_1 = points[n - 1];
    for (int i = 1; i <= n - 2; i++) {
      auto pi = points[i];
      auto ti = t[i];
      for (int k = 1; k <= n - 2; k++) {
        // (1-ti)^(n-1-k) * ti^k n-1Ck pk
        auto coefficientK =
            pow(1 - ti, n - 1 - k) * pow(ti, k) * binomial(n - 1, k);
        // pi -(1-t)^(n-1) p0 - t^(n-1) pn-1
        auto expectedValue =
            pi - (pow(1 - ti, n - 1) * p0) - (pow(ti, n - 1) * pn_1);
        A._(2 * i - 1, 2 * k - 1) = coefficientK;
        b._(2 * i - 1, 1) = expectedValue.x;
        A._(2 * i, 2 * k) = coefficientK;
        b._(2 * i, 1) = expectedValue.y;
      }
    }

    // solve
    auto c = A.inverse() * b;

    // set origin, end, and control points
    this->points.resize(n);
    this->points[0] = p0;
    this->points[n - 1] = pn_1;
    for (int i = 1; i <= n - 2; i++)
      this->points[i] = Point(c._(2 * i - 1, 1), c._(2 * i, 1));
  }
};

#endif // VULCAD_DRAW_SHAPES_BEZIER
