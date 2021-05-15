#if !defined(TUTORIAL_VULKAN_PHYSICAL_DEVICE)
#define TUTORIAL_VULKAN_PHYSICAL_DEVICE

#include "../window/swapChain.cc"
#include "queue.cc"
#include <set>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class PhysicalDevice {

public:
  VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
  QueueFamilyIndices queueFamilyIndices;

  PhysicalDevice(VkInstance instance, VkSurfaceKHR surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0)
      throw std::runtime_error("failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto &device : devices) {
      if (this->isDeviceSuitable(device, surface)) {
        this->vkPhysicalDevice = device;
        break;
      }
    }
    if (this->vkPhysicalDevice == VK_NULL_HANDLE)
      throw std::runtime_error("failed to find a suitable GPU!");
  }

  uint32_t findMemoryType(uint32_t type, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties availableProperties;
    vkGetPhysicalDeviceMemoryProperties(this->vkPhysicalDevice,
                                        &availableProperties);
    for (uint32_t i = 0; i < availableProperties.memoryTypeCount; i++) {
      if ((type & (1 << i)) &&
          (availableProperties.memoryTypes[i].propertyFlags & properties) ==
              properties)
        return i;
    }
    throw std::runtime_error("failed to find suitable memory type!");
  }

private:
  void findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             queueFamilies.data());

    for (int i = 0; i < queueFamilies.size(); i++) {
      if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        this->queueFamilyIndices.graphicsFamilyIndex = i;

      VkBool32 supportsSurface = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface,
                                           &supportsSurface);
      if (supportsSurface)
        this->queueFamilyIndices.surfaceFamilyIndex = i;

      if (this->queueFamilyIndices.isComplete())
        break;
    }
  }

  bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    this->findQueueFamilies(device, surface);
    return this->queueFamilyIndices.isComplete() &&
           PhysicalDevice::supportsExtensions(device,
                                              SwapChain::EXTENSION_NAMES) &&
           SwapChain::isSurpportedBy(device, surface);
  }

  static bool supportsExtensions(VkPhysicalDevice device,
                                 std::vector<const char *> extensionNames) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         availableExtensions.data());
    std::set<std::string> requiredExtensions(extensionNames.begin(),
                                             extensionNames.end());
    for (const auto &extension : availableExtensions) {
      requiredExtensions.erase(extension.extensionName);
    }
    return requiredExtensions.empty();
  }
};

#endif // TUTORIAL_VULKAN_PHYSICAL_DEVICE
