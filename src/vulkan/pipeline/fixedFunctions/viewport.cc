#if !defined(TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VIEWPORT)
#define TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VIEWPORT

#include <vulkan/vulkan.h>

class Viewport {
  static VkPipelineViewportStateCreateInfo
  getCreateInfo(VkExtent2D swapChainExtent) {
    auto viewport = VkViewport{
        .x = 0.0f,
        .y = 0.0f,
        .width = (float)swapChainExtent.width,
        .height = (float)swapChainExtent.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
    };
    auto scissor = VkRect2D{
        .offset = {0, 0},
        .extent = swapChainExtent,
    };

    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor,
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_VIEWPORT
