#include "draw/draw.cc"
#include "vulcad.h"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    auto draw = Draw();
    draw.line({}, {.5, .5}, {1, 0, 0});
    draw.line({}, {0, .5}, {0, 1, 0});
    draw.line({}, {1, 0}, {0, 0, 1});
    draw.circle({}, .7, {.5, .5, 0});
    draw.circle({}, .5, {0, .5, .5});
    draw.circle({}, .2, {.5, 0, .5});
    draw.circle({}, .1, {.2, .4, .8});
    draw.bezier({}, {.4, .6}, {.8, 0});
    draw.bezier({}, {-.27, -.6}, {-.54, .6}, {-.8, 0});
    draw.show();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}