#if !defined(TUTORIAL_VULKAN_DEVICE_QUEUE)
#define TUTORIAL_VULKAN_DEVICE_QUEUE

#include <optional>
#include <stdint.h>
#include <tuple>
#include <vulkan/vulkan.h>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamilyIndex;
  std::optional<uint32_t> surfaceFamilyIndex;

  bool isComplete() {
    return this->graphicsFamilyIndex.has_value() &&
           this->surfaceFamilyIndex.has_value();
  }
};

class Queue {
public:
  /**
   * @return [graphicsQueue, presentQueue]
   */
  static std::tuple<VkQueue, VkQueue>
  get(VkDevice device, QueueFamilyIndices queueFamilyIndices) {
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    vkGetDeviceQueue(device, queueFamilyIndices.graphicsFamilyIndex.value(), 0,
                     &graphicsQueue);
    vkGetDeviceQueue(device, queueFamilyIndices.surfaceFamilyIndex.value(), 0,
                     &presentQueue);
    return std::make_tuple(graphicsQueue, presentQueue);
  }
};

#endif // TUTORIAL_VULKAN_DEVICE_QUEUE
