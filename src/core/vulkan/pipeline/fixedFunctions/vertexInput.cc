#if !defined(VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT)
#define VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT

#include "../../../../vulcad.h"
#include <array>
#include <vulkan/vulkan.h>

class VertexInput {
  inline static std::array<VkVertexInputAttributeDescription, 2>
      attributeDescriptions;
  inline static VkVertexInputBindingDescription bindingDescription = {};

public:
  static VkPipelineVertexInputStateCreateInfo getCreateInfo() {
    VertexInput::attributeDescriptions =
        vulcad::Vertex::getAttributeDescriptions();
    VertexInput::bindingDescription = vulcad::Vertex::getBindingDescription();
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

#endif // VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT
