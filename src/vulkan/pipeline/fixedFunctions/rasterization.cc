#if !defined(TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_RASTERIZATION)
#define TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_RASTERIZATION

#include <vulkan/vulkan.h>

class Rasterization {
public:
  static VkPipelineRasterizationStateCreateInfo getCreateInfo() {
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f,
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_RASTERIZATION
