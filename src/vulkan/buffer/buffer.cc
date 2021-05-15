#if !defined(TUTORIAL_VULKAN_BUFFER_BUFFER)
#define TUTORIAL_VULKAN_BUFFER_BUFFER

#include "../device/physicalDevice.cc"
#include "vertex.cc"
#include <vector>
#include <vulkan/vulkan.h>

class Buffer {
protected:
  VkDeviceMemory memory;

public:
  VkBuffer vkBuffer;

  void copyTo(VkDevice device, VkCommandPool &commandPool, VkBuffer dstBuffer,
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
    vkCmdCopyBuffer(commandBuffer, this->vkBuffer, dstBuffer, 1, &copyRegion);

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

  void kill(VkDevice device) {
    vkDestroyBuffer(device, this->vkBuffer, nullptr);
    vkFreeMemory(device, this->memory, nullptr);
  }

  template <class Data>
  void write(VkDevice device, size_t bufferSize, Data *dataToWrite) {
    void *data;
    vkMapMemory(device, this->memory, 0, bufferSize, 0, &data);
    memcpy(data, dataToWrite, bufferSize);
    vkUnmapMemory(device, this->memory);
  }

protected:
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
      throw std::runtime_error("failed to create buffer!");

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
};

#endif // TUTORIAL_VULKAN_BUFFER_BUFFER
