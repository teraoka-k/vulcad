#if !defined(VULCAD_CORE_VULKAN_PIPELINE_PIPELINE_LAYOUT)
#define VULCAD_CORE_VULKAN_PIPELINE_PIPELINE_PIPELINE_LAYOUT

#include "../descriptor/descriptorSetLayout.cc"
#include <vulkan/vulkan.h>

class PipelineLayout {

public:
  DescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout vkPipelineLayout;

  PipelineLayout() {} // only to use this instance as a class member variable
  PipelineLayout(VkDevice device) {
    this->descriptorSetLayout = DescriptorSetLayout(device);
    VkPipelineLayoutCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 1,
        .pSetLayouts = &this->descriptorSetLayout.vkDescriptorSetLayout,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr,
    };
    if (vkCreatePipelineLayout(device, &createInfo, nullptr,
                               &this->vkPipelineLayout) != VK_SUCCESS)
      throw std::runtime_error("failed to create pipeline layout");
  }

  void kill(VkDevice device) {
    this->descriptorSetLayout.kill(device);
    vkDestroyPipelineLayout(device, this->vkPipelineLayout, nullptr);
  }
};

#endif // VULCAD_CORE_VULKAN_PIPELINE_PIPELINE_LAYOUT
