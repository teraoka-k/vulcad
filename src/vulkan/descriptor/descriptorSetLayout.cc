#if !defined(TUTORIAL_VULKAN_PIPELINE_DESCRIPTOR_SET_LAYOUT)
#define TUTORIAL_VULKAN_PIPELINE_DESCRIPTOR_SET_LAYOUT

#include <vulkan/vulkan.h>

class DescriptorSetLayout {

public:
  VkDescriptorSetLayout vkDescriptorSetLayout;

  DescriptorSetLayout() {}
  DescriptorSetLayout(VkDevice device) {
    VkDescriptorSetLayoutBinding descriptorSetLayoutBinding = {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = nullptr,
    };

    VkDescriptorSetLayoutCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &descriptorSetLayoutBinding,
    };

    if (vkCreateDescriptorSetLayout(device, &createInfo, nullptr,
                                    &this->vkDescriptorSetLayout) != VK_SUCCESS)
      throw std::runtime_error("failed to create descriptor set layout!");
  }

  void kill(VkDevice device) {
    vkDestroyDescriptorSetLayout(device, this->vkDescriptorSetLayout, nullptr);
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_DESCRIPTOR_SET_LAYOUT
