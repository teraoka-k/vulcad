#if !defined(TUTORIAL_VULKAN_FRAMEBUFFER)
#define TUTORIAL_VULKAN_FRAMEBUFFER

#include <vector>
#include <vulkan/vulkan.h>

class Framebuffer {

public:
  std::vector<VkFramebuffer> swapChainFramebuffers;

  Framebuffer(std::vector<VkImageView> swapChainImageViews,
              VkRenderPass renderPass, VkExtent2D swapChainExtent,
              VkDevice device) {
    this->swapChainFramebuffers.resize(swapChainImageViews.size());
    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
      auto createInfo = this->getCreateInfo(renderPass, &swapChainImageViews[i],
                                            swapChainExtent);
      if (vkCreateFramebuffer(device, &createInfo, nullptr,
                              &this->swapChainFramebuffers[i]) != VK_SUCCESS)
        throw std::runtime_error("failed to create framebuffer!");
    }
  }

  void kill(VkDevice device) {
    for (auto framebuffer : this->swapChainFramebuffers)
      vkDestroyFramebuffer(device, framebuffer, nullptr);
  }

private:
  VkFramebufferCreateInfo getCreateInfo(VkRenderPass renderPass,
                                        VkImageView *swapChainImageView,
                                        VkExtent2D swapChainExtent) {
    return {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = swapChainImageView,
        .width = swapChainExtent.width,
        .height = swapChainExtent.height,
        .layers = 1,
    };
  }
};

#endif // TUTORIAL_VULKAN_FRAMEBUFFER
