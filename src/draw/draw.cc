#if !defined(VULCAD_DRAW_DRAW)
#define VULCAD_DRAW_DRAW

#include "../vulcad.h"
#include "spline.cc"
#include "vec.cc"
#include "vector"
#include <math.h>

class Draw {
public:
  Draw() {}

  void bezier(Vec origin, Vec control, Vec end, uint16_t precision = 100) {
    float dt = 1.f / (float)precision;
    auto p2 = origin;
    for (float t = 0.f; t <= 1.f; t += dt) {
      auto p0 = (1 - t) * origin + t * control;
      auto p1 = (1 - t) * control + t * end;
      auto p2New = (1 - t) * p0 + t * p1;
      this->line(p2, p2New);
      p2 = p2New;
    }
  }

  void bezier(Vec origin, Vec control1, Vec control2, Vec end,
              uint16_t precision = 100) {
    float dt = 1.f / (float)precision;
    auto p5 = origin;
    for (float t = 0.f; t <= 1.f; t += dt) {
      auto p0 = (1 - t) * origin + t * control1;
      auto p1 = (1 - t) * control1 + t * control2;
      auto p2 = (1 - t) * control2 + t * end;
      auto p3 = (1 - t) * p0 + t * p1;
      auto p4 = (1 - t) * p1 + t * p2;
      auto p5New = (1 - t) * p3 + t * p4;
      this->line(p5, p5New);
      p5 = p5New;
    }
  }

  void circle(Vec c, float r, Vec rgb = {1, 1, 1}, uint16_t precision = 100) {
    auto theta = .0f;
    const auto dTheta = 2 * M_PI / (float)precision;
    for (int i = 0; i < precision; i++) {
      auto thetaNew = theta + dTheta;
      auto origin = c + r * Vec(cos(theta), sin(theta));
      auto end = c + r * Vec(cos(thetaNew), sin(thetaNew));
      this->line(origin, end, rgb);
      theta = thetaNew;
    }
  }

  void line(Vec origin, Vec end, Vec rgb = {1, 1, 1}) {
    this->indices.push_back(this->vertices.size());
    this->vertices.push_back({{origin.x, origin.y, 0}, {1, 1, 1}});
    this->indices.push_back(this->vertices.size());
    this->vertices.push_back({{end.x, end.y, 0}, {rgb.x, rgb.y, rgb.z}});
  }

  void spline(std::vector<Vec> points, u_int16_t precision = 100) {
    auto spline = Spline(points);
    for (auto &curve : spline.curves) {
      auto [xOrigin, xEnd] = curve.domain;
      float t = 0;
      float dt = 1.f / (float)precision;
      while (t < 1) {
        auto t1 = t + dt;
        auto x0 = (1 - t) * xOrigin + t * xEnd;
        auto x1 = (1 - t1) * xOrigin + t1 * xEnd;
        auto p0 = curve.getPointAt(x0);
        auto p1 = curve.getPointAt(x1);
        this->line(p0, p1);
        [[unlikely]] if (t1 >= 1) this->line(p1, curve.getPointAt(xEnd));
        t = t1;
      }
    }
  }

  void show() { vulcad::show(this->vertices, this->indices); };

private:
  std::vector<vulcad::Vertex> vertices;
  std::vector<uint16_t> indices;
};

#endif // VULCAD_DRAW_DRAW
