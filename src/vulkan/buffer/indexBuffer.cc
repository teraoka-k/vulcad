#if !defined(TUTORIAL_VULKAN_BUFFER_INDEX_BUFFER)
#define TUTORIAL_VULKAN_BUFFER_INDEX_BUFFER

#include "../device/physicalDevice.cc"
#include "buffer.cc"
#include "stagingBuffer.cc"
#include <vector>
#include <vulkan/vulkan.h>

class IndexBuffer : public Buffer {

public:
  std::vector<uint16_t> indices;

  IndexBuffer() {}
  IndexBuffer(VkDevice device, PhysicalDevice physicalDevice,
              std::vector<uint16_t> indices, VkCommandPool &commandPool,
              VkQueue graphicsQueue) {
    this->indices = indices;
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
    this->create(
        device, physicalDevice, bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->vkBuffer, this->memory);
    auto stagingBuffer =
        StagingBuffer(device, physicalDevice, bufferSize, indices.data());
    stagingBuffer.copyTo(device, commandPool, this->vkBuffer, bufferSize,
                         graphicsQueue);
    stagingBuffer.kill(device);
  }
};

#endif // TUTORIAL_VULKAN_BUFFER_INDEX_BUFFER
