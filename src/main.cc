#include "app.cc"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
  try {
    App().run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}