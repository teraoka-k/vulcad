#if !defined(VULCAD_CORE_VULKAN_DESCRIPTOR_SET)
#define VULCAD_CORE_VULKAN_DESCRIPTOR_SET

#include "../buffer/uniformBuffer.cc"
#include <glm/glm.hpp>
#include <vector>
#include <vulkan/vulkan.h>

class DescriptorSet {

public:
  std::vector<VkDescriptorSet> vkDescriptorSets;

  DescriptorSet() {}
  DescriptorSet(VkDevice device, VkDescriptorPool pool,
                VkDescriptorSetLayout setLayout, uint32_t setCount,
                std::vector<UniformBuffer> &uniformBuffers) {
    std::vector<VkDescriptorSetLayout> setLayouts(setCount, setLayout);
    VkDescriptorSetAllocateInfo allocateInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = pool,
        .descriptorSetCount = setCount,
        .pSetLayouts = setLayouts.data(),
    };
    this->vkDescriptorSets.resize(setCount);
    if (vkAllocateDescriptorSets(device, &allocateInfo,
                                 vkDescriptorSets.data()) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate descriptor sets!");

    for (size_t i = 0; i < setCount; i++) {
      VkDescriptorBufferInfo bufferInfo = {
          .buffer = uniformBuffers[i].vkBuffer,
          .offset = 0,
          .range = sizeof(glm::mat4),
      };
      VkWriteDescriptorSet writeSet = {
          .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
          .dstSet = this->vkDescriptorSets[i],
          .dstBinding = 0,
          .dstArrayElement = 0,
          .descriptorCount = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
          .pImageInfo = nullptr,
          .pBufferInfo = &bufferInfo,
          .pTexelBufferView = nullptr,
      };
      vkUpdateDescriptorSets(device, 1, &writeSet, 0, nullptr);
    }
  }
};

#endif // VULCAD_CORE_VULKAN_DESCRIPTOR_SET
