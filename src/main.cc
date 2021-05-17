// #include "core/app.cc"
#include "vulcad.h"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    // App::run(
    vulcad::show(
        {
            {{0, 0, 0}, {0, 1, 1}},
            {{.5, 0, 0}, {1, 0, 1}},
            {{.5, .5, 0}, {1, 1, 0}},
            {{0, .5, 0}, {1, 1, 0}},
        },
        {0, 1, 1, 2, 2, 3, 3, 1, 0, 3, 0, 2});
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}