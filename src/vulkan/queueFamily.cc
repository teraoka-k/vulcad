#if !defined(TUTORIAL_VULKAN_QUEUE_FAMILY)
#define TUTORIAL_VULKAN_QUEUE_FAMILY

#include <optional>
#include <stdint.h>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamilyIndex;
  std::optional<uint32_t> surfaceFamilyIndex;

  bool isComplete() {
    return this->graphicsFamilyIndex.has_value() &&
           this->surfaceFamilyIndex.has_value();
  }
};

#endif // TUTORIAL_VULKAN_QUEUE_FAMILY