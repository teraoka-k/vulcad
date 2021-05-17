#include "vulcad.h"
#include "core/app.cc"

void vulcad::show(std::vector<vulcad::Vertex> vertices,
                  std::vector<uint16_t> indices) {
  App::run(vertices, indices);
}
