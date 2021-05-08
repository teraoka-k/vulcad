#if !defined(TUTORIAL_VULKAN_COMMAND_COMMAND_BUFFER)
#define TUTORIAL_VULKAN_COMMAND_COMMAND_BUFFER

#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class CommandBuffer {

public:
  std::vector<VkCommandBuffer> commandBuffers;

  CommandBuffer(std::vector<VkFramebuffer> swapChainFramebuffers,
                VkCommandPool commandPool, VkDevice device,
                VkExtent2D swapChainExtent, VkRenderPass renderPass,
                VkPipeline pipeline) {
    this->commandBuffers.resize(swapChainFramebuffers.size());
    auto allocateInfo = this->getAllocateInfo(commandPool);
    if (vkAllocateCommandBuffers(device, &allocateInfo,
                                 this->commandBuffers.data()) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate command buffers!");
    this->record(swapChainExtent, renderPass, swapChainFramebuffers, pipeline);
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

  void record(VkExtent2D swapChainExtent, VkRenderPass renderPass,
              std::vector<VkFramebuffer> swapChainFramebuffers,
              VkPipeline pipeline) {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
        .pInheritanceInfo = nullptr,
    };
    for (int i = 0; i < this->commandBuffers.size(); i++) {
      if (vkBeginCommandBuffer(this->commandBuffers[i], &beginInfo) !=
          VK_SUCCESS)
        throw std::runtime_error("failed to begin recording command buffer!");
      this->recordRenderPass(swapChainExtent, renderPass,
                             swapChainFramebuffers[i], &this->commandBuffers[i],
                             pipeline);
      if (vkEndCommandBuffer(this->commandBuffers[i]) != VK_SUCCESS)
        throw std::runtime_error("failed to record command buffer!");
    }
  }

  void recordRenderPass(VkExtent2D swapChainExtent, VkRenderPass renderPass,
                        VkFramebuffer swapChainFramebuffer,
                        VkCommandBuffer *commandBuffer, VkPipeline pipeline) {
    VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    VkRenderPassBeginInfo renderPassInfo = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = renderPass,
        .framebuffer = swapChainFramebuffer,
        .renderArea =
            {
                .offset = {0, 0},
                .extent = swapChainExtent,
            },
        .clearValueCount = 1,
        .pClearValues = &clearColor,
    };
    vkCmdBeginRenderPass(*commandBuffer, &renderPassInfo,
                         VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      pipeline);
    vkCmdDraw(*commandBuffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(*commandBuffer);
  }
};

#endif // TUTORIAL_VULKAN_COMMAND_COMMAND_BUFFER
