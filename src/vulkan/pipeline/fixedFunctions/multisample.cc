#if !defined(TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_MULTISAMPLE)
#define TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_MULTISAMPLE

#include <vulkan/vulkan.h>

class Multisample {
  static VkPipelineMultisampleStateCreateInfo getCreateInfo() {
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .sampleShadingEnable = VK_FALSE,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .minSampleShading = 1.0f,
        .pSampleMask = nullptr,
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable = VK_FALSE,
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_MULTISAMPLE
