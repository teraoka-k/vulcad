
#if !defined(TUTORIAL_VULKAN_VERTEX_VERTEX)
#define TUTORIAL_VULKAN_VERTEX_VERTEX

#include <array>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

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

#endif // TUTORIAL_VULKAN_VERTEX_VERTEX
