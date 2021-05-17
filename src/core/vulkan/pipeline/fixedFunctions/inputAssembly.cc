#if !defined(VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_INPUT_ASSEMBLY)
#define VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_INPUT_ASSEMBLY

#include <vulkan/vulkan.h>

class InputAssembly {
public:
  static VkPipelineInputAssemblyStateCreateInfo getCreateInfo() {
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };
  }
};

#endif // VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_INPUT_ASSEMBLY
