#include "draw/drawer.cc"
#include "draw/dxf/dxf.cc"
#include "draw/shapes/bezier.cc"
#include "draw/shapes/point.cc"
#include "draw/shapes/spline.cc"
#include "math/matrix.cc"
#include "vulcad.h"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    Line l1({}, {.5, .5}), l2({}, {1, 0});

    auto drawer = Drawer();
    drawer.draw(l1, {0, 1, 5});
    drawer.draw(l2, {1, 5, 1});

    Circle c1({}, .7), c2({}, .5), c3({}, .2), c4({}, .1);
    drawer.draw(c1, {0, 10, 50}, 7);
    drawer.draw(c2, {0, 5, 25}, 5);
    drawer.draw(c3, {0, 1, 5}, 3);
    drawer.draw(c4, {30, 50, 0});

    Bezier b({{-.37, 0}, {-.54, .6}, {-.7, -.7}, {-.88, .2}});
    drawer.draw(b, {0, 10, 50});

    Point O = {.0001, .0001}, p1 = {-.2, -.3}, p2 = {-.1, .2}, p3 = {.1, .3},
          p4 = {.4, .2}, p5 = {.7, .6};
    auto points = {p1, p2, O, p3, p4, p5};
    for (auto &p : points)
      drawer.draw(p, {0, 10, 50});

    Spline spline(points);
    drawer.draw(spline, {16, 64, 255}, 100);

    drawer.show();

    Dxf::write("line", l1);
    Dxf::write("circle", c1);
    Dxf::write("point", p1);
    Dxf::write("spline", spline);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}