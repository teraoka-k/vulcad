#if !defined(TUTORIAL_VULKAN_COMMAND_COMMAND_POOL)
#define TUTORIAL_VULKAN_COMMAND_COMMAND_POOL

#include "../device/queue.cc"
#include <vulkan/vulkan.h>

class CommandPool {

public:
  VkCommandPool vkCommandPool;

  CommandPool() {}
  CommandPool(QueueFamilyIndices queueFamilyIndices, VkDevice device) {
    auto createInfo = this->getCreateInfo(queueFamilyIndices);
    if (vkCreateCommandPool(device, &createInfo, nullptr, &vkCommandPool) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to create command pool!");
  }

  void kill(VkDevice device) {
    vkDestroyCommandPool(device, this->vkCommandPool, nullptr);
  }

private:
  VkCommandPoolCreateInfo getCreateInfo(QueueFamilyIndices queueFamilyIndices) {
    return {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = 0,
        .queueFamilyIndex = queueFamilyIndices.graphicsFamilyIndex.value(),
    };
  }
};

#endif // TUTORIAL_VULKAN_COMMAND_COMMAND_POOL
