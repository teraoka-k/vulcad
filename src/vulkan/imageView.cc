#if !defined(TUTORIAL_VULKAN_IMAGE_VIEW)
#define TUTORIAL_VULKAN_IMAGE_VIEW

#include "swapChain.cc"
#include <vector>
#include <vulkan/vulkan.h>

class ImageView {

public:
  std::vector<VkImageView> swapChainImageViews;

  ImageView(VkDevice device, SwapChain swapChain) {
    auto images = swapChain.getImages(device);
    this->swapChainImageViews.resize(images.size());
    for (int i = 0; i < images.size(); i++) {
      auto createInfo = ImageView::getCreateInfo(images[i], swapChain.format);
      if (vkCreateImageView(device, &createInfo, nullptr,
                            &swapChainImageViews[i]) != VK_SUCCESS)
        throw std::runtime_error("failed to create image views");
    }
  }

  void kill(VkDevice device) {
    for (auto imageView : this->swapChainImageViews)
      vkDestroyImageView(device, imageView, nullptr);
  }

private:
  static VkImageViewCreateInfo getCreateInfo(VkImage image, VkFormat format) {
    VkImageViewCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext = NULL,
        .flags = 0,
        .image = image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = format,
    };
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;
    return createInfo;
  }
};

#endif // TUTORIAL_VULKAN_IMAGE_VIEW
