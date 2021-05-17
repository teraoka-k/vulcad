#if !defined(VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_VIEWPORT)
#define VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_VIEWPORT

#include <vulkan/vulkan.h>

class Viewport {
  // save variable in static memory to avoid segmentation fault
  inline static VkViewport viewport;
  inline static VkRect2D scissor;

public:
  static VkPipelineViewportStateCreateInfo
  getCreateInfo(VkExtent2D swapChainExtent) {
    Viewport::viewport = VkViewport{
        .x = 0.0f,
        .y = 0.0f,
        .width = (float)swapChainExtent.width,
        .height = (float)swapChainExtent.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
    };
    Viewport::scissor = VkRect2D{
        .offset = {0, 0},
        .extent = swapChainExtent,
    };

    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &Viewport::viewport,
        .scissorCount = 1,
        .pScissors = &Viewport::scissor,
    };
  }
};

#endif // VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_VIEWPORT
