#if !defined(VULCAD_CORE_VULKAN_SWAP_CHAIN)
#define VULCAD_CORE_VULKAN_SWAP_CHAIN

#include "../device/queue.cc"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>
#include <vulkan/vulkan.h>

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR surfaceCapabilities;
  std::vector<VkSurfaceFormatKHR> surfaceFormats;
  std::vector<VkPresentModeKHR> presentModes;
};

class SwapChain {
  uint32_t imageCount;

public:
  VkExtent2D extent;
  VkFormat format;
  VkSwapchainKHR vkSwapChain;

  inline static const std::vector<const char *> EXTENSION_NAMES = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  SwapChain() {}
  SwapChain(VkPhysicalDevice physicalDevice,
            QueueFamilyIndices queueFamilyIndices, VkDevice logicalDevice,
            VkSurfaceKHR surface, GLFWwindow *window) {
    auto createInfo = this->getCreateInfo(physicalDevice, queueFamilyIndices,
                                          surface, window);
    if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr,
                             &this->vkSwapChain) != VK_SUCCESS)
      throw std::runtime_error("failed to create swap chain");
  }

  std::vector<VkImage> getImages(VkDevice device) {
    std::vector<VkImage> images;
    vkGetSwapchainImagesKHR(device, this->vkSwapChain, &this->imageCount,
                            nullptr);
    images.resize(imageCount);
    vkGetSwapchainImagesKHR(device, this->vkSwapChain, &this->imageCount,
                            images.data());
    return images;
  }

  static bool isSurpportedBy(VkPhysicalDevice device, VkSurfaceKHR surface) {
    auto supportDetails = SwapChain::getSupportDetails(device, surface);
    return !supportDetails.surfaceFormats.empty() &&
           !supportDetails.presentModes.empty();
  }

  void kill(VkDevice device) {
    vkDestroySwapchainKHR(device, this->vkSwapChain, nullptr);
  }

private:
  VkSwapchainCreateInfoKHR getCreateInfo(VkPhysicalDevice physicalDevice,
                                         QueueFamilyIndices queueFamilyIndices,
                                         VkSurfaceKHR surface,
                                         GLFWwindow *window) {
    auto supportDetails = SwapChain::getSupportDetails(physicalDevice, surface);
    auto surfaceFormat =
        SwapChain::selectSurfaceFormat(supportDetails.surfaceFormats);
    auto presentMode =
        SwapChain::selectPresentMode(supportDetails.presentModes);
    this->extent =
        SwapChain::selectExtend2D(supportDetails.surfaceCapabilities, window);
    this->imageCount = supportDetails.surfaceCapabilities.minImageCount + 1;
    if (supportDetails.surfaceCapabilities.maxImageCount > 0 &&
        this->imageCount > supportDetails.surfaceCapabilities.maxImageCount)
      this->imageCount = supportDetails.surfaceCapabilities.maxImageCount;

    const bool isConcurrentQueue = queueFamilyIndices.graphicsFamilyIndex !=
                                   queueFamilyIndices.surfaceFamilyIndex;
    uint32_t pQueueFamilyIndices[] = {
        queueFamilyIndices.graphicsFamilyIndex.value(),
        queueFamilyIndices.surfaceFamilyIndex.value()};

    return {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = this->imageCount,
        .imageFormat = (this->format = surfaceFormat.format),
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = this->extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = isConcurrentQueue ? VK_SHARING_MODE_CONCURRENT
                                              : VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = (uint32_t)(isConcurrentQueue ? 2 : 0),
        .pQueueFamilyIndices =
            isConcurrentQueue ? pQueueFamilyIndices : nullptr,
        .preTransform = supportDetails.surfaceCapabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE,
    };
  }

  static SwapChainSupportDetails getSupportDetails(VkPhysicalDevice device,
                                                   VkSurfaceKHR surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
                                              &details.surfaceCapabilities);
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,
                                         nullptr);
    if (formatCount != 0) {
      details.surfaceFormats.resize(formatCount);
      vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,
                                           details.surfaceFormats.data());
    }
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
                                              &presentModeCount, nullptr);
    if (presentModeCount != 0) {
      details.presentModes.resize(presentModeCount);
      vkGetPhysicalDeviceSurfacePresentModesKHR(
          device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
  }

  static VkExtent2D selectExtend2D(VkSurfaceCapabilitiesKHR capabilities,
                                   GLFWwindow *window) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
      return capabilities.currentExtent;
    } else {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      return VkExtent2D{
          std::clamp((uint32_t)width, capabilities.minImageExtent.width,
                     capabilities.maxImageExtent.width),
          std::clamp((uint32_t)height, capabilities.minImageExtent.height,
                     capabilities.maxImageExtent.height)};
    }
  }

  static VkPresentModeKHR selectPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes) {
    for (const auto &availablePresentMode : availablePresentModes) {
      if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        return availablePresentMode;
    }
    return VK_PRESENT_MODE_FIFO_KHR;
  }

  static VkSurfaceFormatKHR
  selectSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) {
    for (const auto &availableFormat : availableFormats) {
      if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
          availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        return availableFormat;
    }

    return availableFormats[0];
  }
};

#endif // VULCAD_CORE_VULKAN_SWAP_CHAIN
