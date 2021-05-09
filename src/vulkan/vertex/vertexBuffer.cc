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
  VertexBuffer(VkDevice device, PhysicalDevice physicalDevice) {
    this->vertices = {{{0, -.5, 0}, {.5, .5, 0}},
                      {{.5, .5, 0}, {0, .5, .5}},
                      {{-.5, .5, 0}, {.5, 0, .5}}};
    this->createBuffer(device);
    this->allocateMemory(device, physicalDevice);
    this->writeToDevice(device);
  }

  void kill(VkDevice device) {
    vkDestroyBuffer(device, this->vkBuffer, nullptr);
    vkFreeMemory(device, this->memory, nullptr);
  }

private:
  void allocateMemory(VkDevice device, PhysicalDevice physicalDevice) {
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, this->vkBuffer, &memoryRequirements);
    VkMemoryAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = physicalDevice.findMemoryType(
            memoryRequirements.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),

    };
    if (vkAllocateMemory(device, &allocInfo, nullptr, &this->memory) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to allocate vertex buffer memory!");
    vkBindBufferMemory(device, this->vkBuffer, this->memory, 0);
  }

  void createBuffer(VkDevice device) {
    VkBufferCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = this->getSizeInByte(),
        .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };
    if (vkCreateBuffer(device, &createInfo, nullptr, &this->vkBuffer) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to create vertex buffer!");
  }

  void writeToDevice(VkDevice device) {
    void *data;
    auto size = this->getSizeInByte();
    vkMapMemory(device, this->memory, 0, size, 0, &data);
    memcpy(data, this->vertices.data(), (size_t)size);
    vkUnmapMemory(device, this->memory);
  }

  uint64_t getSizeInByte() {
    return sizeof(this->vertices[0]) * this->vertices.size();
  }
};

#endif // TUTORIAL_VULKAN_VERTEX_VERTEX_BUFFER
