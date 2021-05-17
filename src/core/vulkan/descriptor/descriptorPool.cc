#if !defined(VULCAD_CORE_VULKAN_PIPELINE_DESCRIPTOR_POOL)
#define VULCAD_CORE_VULKAN_PIPELINE_DESCRIPTOR_POOL

#include <vulkan/vulkan.h>

class DescryptorPool {

public:
  VkDescriptorPool vkDescriptorPool;

  DescryptorPool() {}
  DescryptorPool(VkDevice device, uint32_t imageCount) {
    VkDescriptorPoolSize size = {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = imageCount,
    };
    VkDescriptorPoolCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = imageCount,
        .poolSizeCount = 1,
        .pPoolSizes = &size,
    };
    if (vkCreateDescriptorPool(device, &createInfo, nullptr,
                               &vkDescriptorPool) != VK_SUCCESS)
      throw std::runtime_error("failed to create descriptor pool!");
  }

  void kill(VkDevice device) {
    vkDestroyDescriptorPool(device, this->vkDescriptorPool, nullptr);
  }
};

#endif // VULCAD_CORE_VULKAN_PIPELINE_DESCRIPTOR_POOL
