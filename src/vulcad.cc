#include "vulcad.h"
#include "core/app.cc"
#include "types.cc"
#include <glm/glm.hpp>

void vulcad::show(std::vector<vulcad::Vertex> vertices,
                  std::vector<uint16_t> indices, ScreenSize screenSize,
                  glm::mat4 model) {
  App::run(vertices, indices, screenSize.width, screenSize.height, model);
}
