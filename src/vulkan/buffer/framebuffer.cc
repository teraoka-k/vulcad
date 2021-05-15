#if !defined(TUTORIAL_VULKAN_FRAMEBUFFER)
#define TUTORIAL_VULKAN_FRAMEBUFFER

#include <vector>
#include <vulkan/vulkan.h>

class Framebuffer {

public:
  std::vector<VkFramebuffer> vkFramebuffers;

  Framebuffer() {}
  Framebuffer(std::vector<VkImageView> imageViews, VkRenderPass renderPass,
              VkExtent2D extent, VkDevice device) {
    this->vkFramebuffers.resize(imageViews.size());
    for (size_t i = 0; i < imageViews.size(); i++) {
      auto createInfo = this->getCreateInfo(renderPass, &imageViews[i], extent);
      if (vkCreateFramebuffer(device, &createInfo, nullptr,
                              &this->vkFramebuffers[i]) != VK_SUCCESS)
        throw std::runtime_error("failed to create framebuffer!");
    }
  }

  void kill(VkDevice device) {
    for (auto framebuffer : this->vkFramebuffers)
      vkDestroyFramebuffer(device, framebuffer, nullptr);
  }

private:
  VkFramebufferCreateInfo getCreateInfo(VkRenderPass renderPass,
                                        VkImageView *imageView,
                                        VkExtent2D extent) {
    return {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = imageView,
        .width = extent.width,
        .height = extent.height,
        .layers = 1,
    };
  }
};

#endif // TUTORIAL_VULKAN_FRAMEBUFFER
