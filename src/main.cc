#include "draw/drawing.cc"
#include "vulcad.h"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    Point O;
    Line l1(O, {0, 75}), l2({75 * (1 - .1618), 0}, O);

    const int maxX = 70;
    const int maxY = 90;
    Drawing drawing({.x = {.min = 0, .max = maxX},
                     .y = {.min = 0, .max = maxY},
                     .z = {.min = -1, .max = 1}},
                    {.width = 900, .height = 900});
    drawing.draw(l1, {0, 1, 5});
    drawing.draw(l2, {1, 5, 1});

    Point center(maxX / 2, maxY / 2);
    Circle c1(center, 16.18),
        c2(center + Point(16.18, 10), 16.18 * (1 - .1618)),
        c3(center + 1.618 * Point(16.18, 10),
           16.18 * (1 - .1618) * (1 - .1618)),
        c4(center + 1.618 * 1.618 * Point(16.18, 10),
           16.18 * (1 - .1618) * (1 - .1618) * (1 - .1618));
    drawing.draw(c1, {0, 10, 50}, 7);
    drawing.draw(c2, {0, 5, 25}, 5);
    drawing.draw(c3, {0, 1, 5}, 3);
    drawing.draw(c4, {30, 50, 0});

    Bezier b({{maxX, maxY}, center, center * 1.618, {0, maxY}});
    drawing.draw(b, {0, 10, 50});

    Point p1 = {12, 23}, p2 = {33, 34}, p3 = {45, 28}, p4 = {62, 23},
          p5 = {77, 31}, p6 = {89, 23};
    auto points = {O, p1, p2, p3, p4, p5, p6};
    // for (auto &p : points)
    // drawing.draw(p, {0, 10, 50});

    Spline spline(points);
    drawing.draw(spline, {16, 64, 255}, 100);

    drawing.show();

    drawing.save("drawing");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}