#if !defined(VULCAD)
#define VULCAD

#include "core/vulkan/buffer/vertex.cc"
#include <array>
#include <glm/glm.hpp>
#include <vector>
#include <vulkan/vulkan.h>

namespace vulcad {

/**
 * @param vertices points
 * @param indices specify points in order so that they forms triangles.
 * e.g. if there are 4 vertices (0, 1, 2, 3),
 * then pass {0, 1, 2, 2, 3, 0} to draw two triangles, {0, 1, 2} and {2, 3, 0}
 */
void show(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
} // namespace vulcad

#endif