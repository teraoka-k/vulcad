#if !defined(TUTORIAL_VULKAN_LOGICAL_DEVICE)
#define TUTORIAL_VULKAN_LOGICAL_DEVICE

#include "physicalDevice.cc"
#include <vulkan/vulkan.h>

class LogicalDevice {
  inline static VkDevice device = VK_NULL_HANDLE;

public:
  static VkDevice init(PhysicalDevice physicalDevice) {
    auto queueCreateInfo =
        LogicalDevice::getQueueCreateInfo(physicalDevice.queueFamilyIndices);
    VkPhysicalDeviceFeatures deviceFeatures{};
    auto createInfo = VkDeviceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .pEnabledFeatures = &deviceFeatures,
    };

    if (vkCreateDevice(physicalDevice.vkPhysicalDevice, &createInfo, nullptr,
                       &LogicalDevice::device) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device");
    }
    return LogicalDevice::device;
  }

  static void kill() { vkDestroyDevice(LogicalDevice::device, nullptr); }

private:
  static VkDeviceQueueCreateInfo
  getQueueCreateInfo(QueueFamilyIndices queueFamilyIndices) {
    float queuePriority = 1.0f;
    return {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queueFamilyIndices.graphicsFamily.value(),
        .queueCount = 1,
        .pQueuePriorities = &queuePriority,
    };
  }
};

#endif // TUTORIAL_VULKAN_LOGICAL_DEVICE
