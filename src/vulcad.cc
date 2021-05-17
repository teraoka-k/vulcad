#include "vulcad.h"
#include "core/app.cc"

void vulcad::show(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
  App::run(vertices, indices);
}
