#if !defined(TUTORIAL_VULKAN_QUEUE_FAMILY)
#define TUTORIAL_VULKAN_QUEUE_FAMILY

#include <optional>
#include <stdint.h>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
};

#endif // TUTORIAL_VULKAN_QUEUE_FAMILY
