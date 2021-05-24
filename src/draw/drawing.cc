#if !defined(VULCAD_DRAW_DRAWING)
#define VULCAD_DRAW_DRAWING

#include "../types.cc"
#include "../vulcad.h"
#include "shapes/bezier.cc"
#include "shapes/circle.cc"
#include "shapes/line.cc"
#include "shapes/point.cc"
#include "shapes/spline.cc"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <variant>
#include <vector>

class Drawing {
  typedef Point RGB;
  inline static const RGB DEFAULT_COLOR = {255, 255, 255};

  CoordinatesRange coordinatesRange;
  ScreenSize screenSize;

public:
  Drawing(CoordinatesRange coordinatesRange, ScreenSize screenSize) {
    this->coordinatesRange = coordinatesRange;
    this->screenSize = screenSize;
  }

  void draw(std::variant<Point, Line, Circle, Bezier, Spline> shape,
            RGB rgb = {255, 255, 255}, u_int16_t precision = 100) {
    if (std::holds_alternative<Point>(shape))
      this->drawPoint(std::get<Point>(shape), rgb);
    else if (std::holds_alternative<Line>(shape))
      this->drawLine(std::get<Line>(shape), rgb);
    else if (std::holds_alternative<Circle>(shape))
      this->drawCircle(std::get<Circle>(shape), rgb, precision);
    else if (std::holds_alternative<Bezier>(shape))
      this->drawBezier(std::get<Bezier>(shape), rgb, precision);
    else if (std::holds_alternative<Spline>(shape))
      this->drawSpline(std::get<Spline>(shape), rgb, precision);
  }

  void show() {
    glm::mat4 model(1.f);
    // normalize coodinates
    auto scale = 2.f / std::max({this->coordinatesRange.x.getDistance(),
                                 this->coordinatesRange.y.getDistance(),
                                 this->coordinatesRange.z.getDistance()});
    model = glm::scale(model, {scale, scale, scale});
    // ordinal x-y plane (horizontal x-axis and vertical y-axis)
    model = glm::rotate(model, glm::radians(90.0f), {0, 0, 1});
    // ordinal x-y plane (origin is at the left bottom)
    model[3].x = 1;
    model[3].y = -1;
    model[3].z = -1;
    vulcad::show(this->vertices, this->indices, this->screenSize, model);
  };

private:
  std::vector<vulcad::Vertex> vertices;
  std::vector<uint16_t> indices;

  void drawBezier(Bezier bezier, RGB rgb = DEFAULT_COLOR,
                  uint16_t precision = 100) {
    float dt = 1.f / (float)precision;
    auto origin = bezier.origin;
    auto control = bezier.control;
    auto end = bezier.end;

    if (bezier.isQuodratic()) {
      auto p2 = origin;
      for (float t = 0.f; t <= 1.f; t += dt) {
        auto p0 = (1 - t) * origin + t * control[0];
        auto p1 = (1 - t) * control[0] + t * end;
        auto p2New = (1 - t) * p0 + t * p1;
        this->drawLine(Line(p2, p2New), rgb);
        p2 = p2New;
      }
    } else if (bezier.isCubic()) {
      auto p5 = origin;
      for (float t = 0.f; t <= 1.f; t += dt) {
        auto p0 = (1 - t) * origin + t * control[0];
        auto p1 = (1 - t) * control[0] + t * control[1];
        auto p2 = (1 - t) * control[1] + t * end;
        auto p3 = (1 - t) * p0 + t * p1;
        auto p4 = (1 - t) * p1 + t * p2;
        auto p5New = (1 - t) * p3 + t * p4;
        this->drawLine(Line(p5, p5New), rgb);
        p5 = p5New;
      }
    }
  }

  void drawCircle(Circle c, RGB rgb = DEFAULT_COLOR, uint16_t precision = 100) {
    auto theta = .0f;
    const float dTheta = 2 * M_PI / (float)precision;
    while (theta < 2 * M_PI) {
      auto newTheta = theta + dTheta;
      auto p0 = c.getPointAt(theta);
      if (newTheta >= 2 * M_PI)
        return this->drawLine(Line(p0, c.getPointAt(0)), rgb);
      auto p1 = c.getPointAt(newTheta);
      this->drawLine(Line(p0, p1), rgb);
      theta = newTheta;
    }
  }

  void drawLine(Line line, RGB rgb = DEFAULT_COLOR) {
    this->indices.push_back(this->vertices.size());
    auto origin = line.origin;
    auto end = line.end;
    this->vertices.push_back({{origin.x, origin.y, 0}, {rgb.x, rgb.y, rgb.z}});
    this->indices.push_back(this->vertices.size());
    this->vertices.push_back({{end.x, end.y, 0}, {rgb.x, rgb.y, rgb.z}});
  }

  void drawPoint(Point &p, RGB rgb = DEFAULT_COLOR) {
    this->drawCircle(Circle(p, 1), rgb);
  }

  void drawSpline(Spline &spline, RGB rgb = DEFAULT_COLOR,
                  u_int16_t precision = 100) {
    for (auto &curve : spline.curves) {
      auto xOrigin = curve.origin.x;
      auto xEnd = curve.end.x;
      float t = 0;
      float dt = 1.f / (float)precision;
      while (t < 1) {
        auto t1 = t + dt;
        auto x0 = (1 - t) * xOrigin + t * xEnd;
        auto x1 = (1 - t1) * xOrigin + t1 * xEnd;
        auto p0 = curve.getPointAt(x0);
        auto p1 = curve.getPointAt(x1);
        this->drawLine(Line(p0, p1), rgb);
        [[unlikely]] if (t1 >= 1) this->drawLine(
            Line(p1, curve.getPointAt(xEnd)), rgb);
        t = t1;
      }
    }
  }
};

#endif // VULCAD_DRAW_DRAWING
