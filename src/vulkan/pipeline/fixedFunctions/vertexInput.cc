#if !defined(TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT)
#define TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT

#include "../../buffer/vertex.cc"
#include <array>
#include <vulkan/vulkan.h>

class VertexInput {
  inline static std::array<VkVertexInputAttributeDescription, 2>
      attributeDescriptions;
  inline static VkVertexInputBindingDescription bindingDescription = {};

public:
  static VkPipelineVertexInputStateCreateInfo getCreateInfo() {
    VertexInput::attributeDescriptions = Vertex::getAttributeDescriptions();
    VertexInput::bindingDescription = Vertex::getBindingDescription();
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &VertexInput::bindingDescription,
        .vertexAttributeDescriptionCount =
            (uint32_t)VertexInput::attributeDescriptions.size(),
        .pVertexAttributeDescriptions =
            VertexInput::attributeDescriptions.data(),
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT
