#if !defined(TUTORIAL_VULKAN_PHYSICAL_DEVICE)
#define TUTORIAL_VULKAN_PHYSICAL_DEVICE

#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class PhysicalDevice {
public:
  PhysicalDevice(VkInstance instance) {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0)
      throw std::runtime_error("failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto &device : devices) {
      if (isDeviceSuitable(device)) {
        physicalDevice = device;
        break;
      }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }
  }

private:
  bool isDeviceSuitable(VkPhysicalDevice device) { return true; }
};

#endif // TUTORIAL_VULKAN_PHYSICAL_DEVICE
