#if !defined(TUTORIAL_VULKAN_PIPELINE_PIPELINE_LAYOUT)
#define TUTORIAL_VULKAN_PIPELINE_PIPELINE_PIPELINE_LAYOUT

#include <vulkan/vulkan.h>

class PipelineLayout {

public:
  VkPipelineLayout vkPipelineLayout;

  PipelineLayout() {} // only to use this instance as a class member variable
  PipelineLayout(VkDevice device) {
    VkPipelineLayoutCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 0,
        .pSetLayouts = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr,
    };
    if (vkCreatePipelineLayout(device, &createInfo, nullptr,
                               &this->vkPipelineLayout) != VK_SUCCESS)
      throw std::runtime_error("failed to create pipeline layout");
  }

  void kill(VkDevice device) {
    vkDestroyPipelineLayout(device, this->vkPipelineLayout, nullptr);
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_PIPELINE_LAYOUT
