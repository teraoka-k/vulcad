#if !defined(TUTORIAL_VULKAN_COMMAND_COMMAND_BUFFER)
#define TUTORIAL_VULKAN_COMMAND_COMMAND_BUFFER

#include "../buffer/framebuffer.cc"
#include "../buffer/indexBuffer.cc"
#include "../buffer/uniformBuffer.cc"
#include "../buffer/vertexBuffer.cc"
#include "../descriptor/descriptorPool.cc"
#include "../descriptor/descriptorSet.cc"
#include "../device/physicalDevice.cc"
#include "../pipeline/pipeline.cc"
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class CommandBuffer {
  Framebuffer framebuffer;
  IndexBuffer indexBuffer;
  DescryptorPool descriptorPool;
  VertexBuffer vertexBuffer;

public:
  std::vector<VkCommandBuffer> commandBuffers;

  CommandBuffer() {}
  CommandBuffer(VkCommandPool commandPool, VkDevice device, VkExtent2D extent,
                Pipeline pipeline, PhysicalDevice physicalDevice,
                VkQueue graphicsQueue, std::vector<VkImageView> imageViews,
                std::vector<UniformBuffer> uniformBuffers) {
    auto countImage = imageViews.size();
    this->framebuffer = Framebuffer(
        imageViews, pipeline.renderPass.vkRenderPass, extent, device);
    this->descriptorPool = DescryptorPool(device, countImage);
    auto descriptorSet =
        DescriptorSet(device, this->descriptorPool.vkDescriptorPool,
                      pipeline.layout.descriptorSetLayout.vkDescriptorSetLayout,
                      countImage, uniformBuffers);

    this->vertexBuffer = VertexBuffer(device, physicalDevice,
                                      {{{-.5, -.5, 0}, {1, 0, 0}},
                                       {{.5, -.5, 0}, {0, 1, 0}},
                                       {{.5, .5, 0}, {0, 0, 1}},
                                       {{-.5, .5, 0}, {1, 1, 1}}},
                                      commandPool, graphicsQueue);
    this->indexBuffer = IndexBuffer(device, physicalDevice, {0, 1, 2, 2, 3, 0},
                                    commandPool, graphicsQueue);

    this->commandBuffers.resize(countImage);
    auto allocateInfo = this->getAllocateInfo(commandPool);
    if (vkAllocateCommandBuffers(device, &allocateInfo,
                                 this->commandBuffers.data()) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate command buffers!");
    this->record(extent, pipeline, device, physicalDevice, commandPool,
                 graphicsQueue, descriptorSet.vkDescriptorSets);
  }

  void free(VkDevice device, VkCommandPool commandPool) {
    vkFreeCommandBuffers(device, commandPool,
                         static_cast<uint32_t>(this->commandBuffers.size()),
                         this->commandBuffers.data());
    this->kill(device);
  }

  void kill(VkDevice device) {
    this->indexBuffer.kill(device);
    this->vertexBuffer.kill(device);
    this->framebuffer.kill(device);
    this->descriptorPool.kill(device);
  }

private:
  VkCommandBufferAllocateInfo getAllocateInfo(VkCommandPool commandPool) {
    return {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = (uint32_t)this->commandBuffers.size(),
    };
  }

  void record(VkExtent2D extent, Pipeline pipeline, VkDevice device,
              PhysicalDevice physicalDevice, VkCommandPool &commandPool,
              VkQueue graphicsQueue,
              std::vector<VkDescriptorSet> descriptorSets) {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
        .pInheritanceInfo = nullptr,
    };
    for (int i = 0; i < this->commandBuffers.size(); i++) {
      if (vkBeginCommandBuffer(this->commandBuffers[i], &beginInfo) !=
          VK_SUCCESS)
        throw std::runtime_error("failed to begin recording command buffer!");
      this->recordRenderPass(extent, this->framebuffer.vkFramebuffers[i],
                             &this->commandBuffers[i], pipeline, device,
                             physicalDevice, commandPool, graphicsQueue,
                             &descriptorSets[i]);
      if (vkEndCommandBuffer(this->commandBuffers[i]) != VK_SUCCESS)
        throw std::runtime_error("failed to record command buffer!");
    }
  }

  void recordRenderPass(VkExtent2D extent, VkFramebuffer framebuffer,
                        VkCommandBuffer *commandBuffer, Pipeline pipeline,
                        VkDevice device, PhysicalDevice physicalDevice,
                        VkCommandPool &commandPool, VkQueue graphicsQueue,
                        VkDescriptorSet *descriptorSet) {
    VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    VkRenderPassBeginInfo renderPassInfo = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = pipeline.renderPass.vkRenderPass,
        .framebuffer = framebuffer,
        .renderArea =
            {
                .offset = {0, 0},
                .extent = extent,
            },
        .clearValueCount = 1,
        .pClearValues = &clearColor,
    };
    vkCmdBeginRenderPass(*commandBuffer, &renderPassInfo,
                         VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      pipeline.vkPipeline);
    VkDeviceSize offsets = 0;
    vkCmdBindVertexBuffers(*commandBuffer, 0, 1, &this->vertexBuffer.vkBuffer,
                           &offsets);
    vkCmdBindIndexBuffer(*commandBuffer, this->indexBuffer.vkBuffer, 0,
                         VK_INDEX_TYPE_UINT16);
    vkCmdBindDescriptorSets(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipeline.layout.vkPipelineLayout, 0, 1,
                            descriptorSet, 0, nullptr);
    vkCmdDrawIndexed(*commandBuffer, indexBuffer.indices.size(), 1, 0, 0, 0);
    vkCmdEndRenderPass(*commandBuffer);
  }
};

#endif // TUTORIAL_VULKAN_COMMAND_COMMAND_BUFFER
