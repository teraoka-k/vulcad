#include "draw/draw.cc"
#include "draw/spline.cc"
#include "math/matrix.cc"
#include "vulcad.h"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    auto draw = Draw();
    draw.line({}, {.5, .5}, {1, 0, 0});
    draw.line({}, {0, .5}, {0, 1, 0});
    draw.line({}, {1, 0}, {0, 0, 1});
    draw.circle({}, .7, {.5, .5, 0}, 10);
    draw.circle({}, .5, {0, .5, .5}, 1000);
    draw.circle({}, .2, {.5, 0, .5}, 1200);
    draw.circle({}, .1, {.2, .4, .8});
    draw.bezier({-.37, 0}, {-.54, .6}, {-.7, -.7}, {-.88, .2});
    Vec O = {.0001, .0001};
    Vec p1 = {-.2, -.3};
    Vec p2 = {-.1, .2};
    Vec p3 = {.1, .3};
    Vec p4 = {.4, .2};
    Vec p5 = {.7, .6};
    auto points = {p1, p2, O, p3, p4, p5};
    for (auto &p : points)
      draw.circle(p, .01);
    draw.spline(points, 100);
    draw.show();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}