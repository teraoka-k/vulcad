#if !defined(TUTORIAL_VULKAN_BUFFER_STAGING_BUFFER)
#define TUTORIAL_VULKAN_BUFFER_STAGING_BUFFER

#include "../physicalDevice.cc"
#include "buffer.cc"
#include <vulkan/vulkan.h>

class StagingBuffer : public Buffer {

public:
  StagingBuffer(VkDevice device, PhysicalDevice physicalDevice,
                VkDeviceSize bufferSize) {
    this->create(device, physicalDevice, bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 this->vkBuffer, this->memory);
  }
};

#endif // TUTORIAL_VULKAN_BUFFER_STAGING_BUFFER
