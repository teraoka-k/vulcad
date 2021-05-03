#if !defined(TUTORIAL_VULKAN_DEVICE_QUEUE)
#define TUTORIAL_VULKAN_DEVICE_QUEUE

#include "physicalDevice.cc"
#include <vulkan/vulkan.h>

class DeviceQueue {
public:
  static VkQueue get(VkDevice device, QueueFamilyIndices queueFamilyIndices) {
    VkQueue graphicsQueue;
    vkGetDeviceQueue(device, queueFamilyIndices.graphicsFamily.value(), 0,
                     &graphicsQueue);
    return graphicsQueue;
  }
};

#endif // TUTORIAL_VULKAN_DEVICE_QUEUE
