#if !defined(VULCAD_CORE_VULKAN_BUFFER_VERTEX_BUFFER)
#define VULCAD_CORE_VULKAN_BUFFER_VERTEX_BUFFER

#include "../device/physicalDevice.cc"
#include "buffer.cc"
#include "stagingBuffer.cc"
#include "vertex.cc"
#include <vector>
#include <vulkan/vulkan.h>

class VertexBuffer : public Buffer {

public:
  std::vector<Vertex> vertices;

  VertexBuffer() {}
  VertexBuffer(VkDevice device, PhysicalDevice physicalDevice,
               std::vector<Vertex> vertices, VkCommandPool &commandPool,
               VkQueue graphicsQueue) {
    this->vertices = vertices;
    auto bufferSize = sizeof(this->vertices[0]) * this->vertices.size();
    this->create(
        device, physicalDevice, bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->vkBuffer, this->memory);
    this->write(device, physicalDevice, bufferSize, commandPool, graphicsQueue);
  }

private:
  void write(VkDevice device, PhysicalDevice physicalDevice,
             VkDeviceSize bufferSize, VkCommandPool &commandPool,
             VkQueue graphicsQueue) {
    auto stagingBuffer = StagingBuffer(device, physicalDevice, bufferSize,
                                       this->vertices.data());
    stagingBuffer.copyTo(device, commandPool, this->vkBuffer, bufferSize,
                         graphicsQueue);
    stagingBuffer.kill(device);
  }
};

#endif // VULCAD_CORE_VULKAN_BUFFER_VERTEX_BUFFER
