#if !defined(TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT)
#define TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT

#include <vulkan/vulkan.h>

class VertexInput {
  static VkPipelineVertexInputStateCreateInfo getCreateInfo() {
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 0,
        .pVertexBindingDescriptions = nullptr,
        .vertexAttributeDescriptionCount = 0,
        .pVertexAttributeDescriptions = nullptr,
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VERTEX_INPUT
