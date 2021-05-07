#if !defined(TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_INPUT_ASSEMBLY)
#define TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_INPUT_ASSEMBLY

#include <vulkan/vulkan.h>

class InputAssembly {
  static VkPipelineInputAssemblyStateCreateInfo getCreateInfo() {
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_FIXED_FUNCTIONS_INPUT_ASSEMBLY
