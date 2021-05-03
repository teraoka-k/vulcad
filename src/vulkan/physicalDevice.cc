#if !defined(TUTORIAL_VULKAN_PHYSICAL_DEVICE)
#define TUTORIAL_VULKAN_PHYSICAL_DEVICE

#include "queueFamily.cc"
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class PhysicalDevice {

public:
  VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
  QueueFamilyIndices queueFamilyIndices;

  PhysicalDevice(VkInstance instance) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0)
      throw std::runtime_error("failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto &device : devices) {
      if (this->isDeviceSuitable(device)) {
        this->vkPhysicalDevice = device;
        break;
      }
    }
    if (this->vkPhysicalDevice == VK_NULL_HANDLE)
      throw std::runtime_error("failed to find a suitable GPU!");
  }

private:
  void findQueueFamilies(VkPhysicalDevice device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             queueFamilies.data());

    for (int i = 0; i < queueFamilies.size(); i++) {
      if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        this->queueFamilyIndices.graphicsFamily = i;
        break;
      }
    }
  }

  bool isDeviceSuitable(VkPhysicalDevice device) {
    this->findQueueFamilies(device);
    return this->queueFamilyIndices.graphicsFamily.has_value();
  }
};

#endif // TUTORIAL_VULKAN_PHYSICAL_DEVICE
