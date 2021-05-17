#if !defined(VULCAD)
#define VULCAD

// #include "core/vulkan/buffer/vertex.cc"
#include <array>
#include <glm/glm.hpp>
#include <vector>
#include <vulkan/vulkan.h>

namespace vulcad {

struct Vertex {
  glm::vec3 xyz;
  glm::vec3 rgb;
  static VkVertexInputBindingDescription getBindingDescription() {
    return {.binding = 0,
            .stride = sizeof(Vertex),
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX};
  }

  static std::array<VkVertexInputAttributeDescription, 2>
  getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    attributeDescriptions[0] = {.location = 0,
                                .binding = 0,
                                .format = VK_FORMAT_R32G32_SFLOAT,
                                .offset = offsetof(Vertex, xyz)};
    attributeDescriptions[1] = {.location = 1,
                                .binding = 0,
                                .format = VK_FORMAT_R32G32B32_SFLOAT,
                                .offset = offsetof(Vertex, rgb)};
    return attributeDescriptions;
  }
};

/**
 * @param vertices points
 * @param indices specify points in order so that they forms triangles.
 * e.g. if there are 4 vertices (0, 1, 2, 3),
 * then pass {0, 1, 2, 2, 3, 0} to draw two triangles, {0, 1, 2} and {2, 3, 0}
 */
void show(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
} // namespace vulcad

#endif