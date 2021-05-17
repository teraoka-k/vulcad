#if !defined(VULCAD_CORE_VULKAN_LOGICAL_DEVICE)
#define VULCAD_CORE_VULKAN_LOGICAL_DEVICE

#include "../window/swapChain.cc"
#include "physicalDevice.cc"
#include "queue.cc"
#include <set>
#include <vector>
#include <vulkan/vulkan.h>

class LogicalDevice {

public:
  VkDevice vkDevice;

  LogicalDevice(PhysicalDevice physicalDevice) {
    auto queueCreateInfos =
        LogicalDevice::getQueueCreateInfo(physicalDevice.queueFamilyIndices);
    VkPhysicalDeviceFeatures deviceFeatures{};
    auto createInfo = VkDeviceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = (uint32_t)queueCreateInfos.size(),
        .pQueueCreateInfos = queueCreateInfos.data(),
        .enabledExtensionCount = (uint32_t)SwapChain::EXTENSION_NAMES.size(),
        .ppEnabledExtensionNames = SwapChain::EXTENSION_NAMES.data(),
        .pEnabledFeatures = &deviceFeatures,
    };

    if (vkCreateDevice(physicalDevice.vkPhysicalDevice, &createInfo, nullptr,
                       &this->vkDevice) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device");
    }
  }

  void kill() { vkDestroyDevice(this->vkDevice, nullptr); }

private:
  static std::vector<VkDeviceQueueCreateInfo>
  getQueueCreateInfo(QueueFamilyIndices queueFamilyIndices) {
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {
        queueFamilyIndices.graphicsFamilyIndex.value(),
        queueFamilyIndices.surfaceFamilyIndex.value()};

    float queuePriority = 1.0f;
    for (auto queueFamily : uniqueQueueFamilies) {
      queueCreateInfos.push_back({
          .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
          .queueFamilyIndex = queueFamily,
          .queueCount = 1,
          .pQueuePriorities = &queuePriority,
      });
    }

    return queueCreateInfos;
  }
};

#endif // VULCAD_CORE_VULKAN_LOGICAL_DEVICE
