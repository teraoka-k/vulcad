#if !defined(VULCAD_CORE_VULKAN_BUFFER_UNIFORM_BUFFER)
#define VULCAD_CORE_VULKAN_BUFFER_UNIFORM_BUFFER

#include "../device/physicalDevice.cc"
#include "buffer.cc"
#include <chrono>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

constexpr VkDeviceSize bufferSize = sizeof(glm::mat4);

class UniformBuffer : public Buffer {

public:
  UniformBuffer() {}
  UniformBuffer(VkDevice device, PhysicalDevice physicalDevice) {
    this->create(device, physicalDevice, bufferSize,
                 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 this->vkBuffer, this->memory);
  }

  void writeMVP(VkDevice device, VkExtent2D extent, glm::mat4 model) {
    glm::mat4 view =
        glm::lookAt(glm::vec3(.001f, .0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
    proj[1][1] *= -1;
    auto MVP = proj * view * model;
    this->write(device, bufferSize, &MVP);
  }
};

#endif // VULCAD_CORE_VULKAN_BUFFER_UNIFORM_BUFFER
