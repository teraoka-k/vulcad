#if !defined(TUTORIAL_VULKAN_VERTEX_VERTEX_BUFFER)
#define TUTORIAL_VULKAN_VERTEX_VERTEX_BUFFER

#include "../physicalDevice.cc"
#include "vertex.cc"
#include <vector>
#include <vulkan/vulkan.h>

class VertexBuffer {
  VkDeviceMemory memory;

public:
  VkBuffer vkBuffer;
  std::vector<Vertex> vertices;

  VertexBuffer() {}
  VertexBuffer(VkDevice device, PhysicalDevice physicalDevice,
               VkCommandPool &commandPool, VkQueue graphicsQueue) {
    this->vertices = {{{0, -.5, 0}, {.5, .5, 0}},
                      {{.5, .5, 0}, {0, .5, .5}},
                      {{-.5, .5, 0}, {.5, 0, .5}}};
    auto bufferSize = sizeof(this->vertices[0]) * this->vertices.size();

    this->create(
        device, physicalDevice, bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->vkBuffer, this->memory);
    this->write(device, physicalDevice, bufferSize, commandPool, graphicsQueue);
  }

  void kill(VkDevice device) {
    vkDestroyBuffer(device, this->vkBuffer, nullptr);
    vkFreeMemory(device, this->memory, nullptr);
  }

private:
  void copyBuffer(VkDevice device, VkCommandPool &commandPool,
                  VkBuffer srcBuffer, VkBuffer dstBuffer,
                  VkDeviceSize deviceSize, VkQueue &graphicsQueue) {
    VkCommandBufferAllocateInfo allocateInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    vkBeginCommandBuffer(commandBuffer, &beginInfo);
    VkBufferCopy copyRegion = {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = deviceSize,
    };
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer,
    };
    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);
    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
  }

  void create(VkDevice device, PhysicalDevice physicalDevice, VkDeviceSize size,
              VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties,
              VkBuffer &buffer, VkDeviceMemory &bufferMemory) {
    VkBufferCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };
    if (vkCreateBuffer(device, &createInfo, nullptr, &buffer) != VK_SUCCESS)
      throw std::runtime_error("failed to create vertex buffer!");

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = physicalDevice.findMemoryType(
            memRequirements.memoryTypeBits, memoryProperties),
    };

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to allocate buffer memory!");

    vkBindBufferMemory(device, buffer, bufferMemory, 0);
  }

  void write(VkDevice device, PhysicalDevice physicalDevice,
             VkDeviceSize bufferSize, VkCommandPool &commandPool,
             VkQueue graphicsQueue) {
    // create staging buffer
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->create(device, physicalDevice, bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingBufferMemory);

    // write vertices to staging buffer
    void *data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, this->vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    // copy data from staging buffer to vertex buffer
    this->copyBuffer(device, commandPool, stagingBuffer, this->vkBuffer,
                     bufferSize, graphicsQueue);

    // clear staging buffer
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
  }
};

#endif // TUTORIAL_VULKAN_VERTEX_VERTEX_BUFFER
