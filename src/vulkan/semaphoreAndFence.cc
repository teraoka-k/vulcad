#if !defined(TUTORIAL_VULKAN_SEMAPHORE)
#define TUTORIAL_VULKAN_SEMAPHORE

#include <tuple>
#include <vector>
#include <vulkan/vulkan.h>

struct imageState {
  VkSemaphore exists;
  VkSemaphore isReadyToPresent;
  VkFence isInUse;
};

class SemaphoreAndFence {

public:
  std::vector<imageState> images;

  SemaphoreAndFence() {
  } // only to use this class as another class's member variable
  /**
   * @param imageCount: number of images available in the swap chain
   */
  SemaphoreAndFence(VkDevice device, uint32_t imageCount) {
    this->images.resize(imageCount);
    auto [semaphoreCreateInfo, fenceCreateInfo] = this->getCreateInfo();
    for (auto &image : this->images) {
      for (auto pSemaphore : {&image.exists, &image.isReadyToPresent}) {
        if (vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr,
                              pSemaphore) != VK_SUCCESS)
          throw std::runtime_error("failed to create semaphores!");
      }
      if (vkCreateFence(device, &fenceCreateInfo, nullptr, &image.isInUse) !=
          VK_SUCCESS)
        throw std::runtime_error("failed to create fences!");
    }
  }

  void kill(VkDevice device) {
    for (auto &image : this->images) {
      for (auto semaphore : {image.exists, image.isReadyToPresent})
        vkDestroySemaphore(device, semaphore, nullptr);
      vkDestroyFence(device, image.isInUse, nullptr);
    }
  }

private:
  std::tuple<VkSemaphoreCreateInfo, VkFenceCreateInfo> getCreateInfo() {
    return std::make_tuple(
        VkSemaphoreCreateInfo{
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        },
        VkFenceCreateInfo{
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT,
        });
  }
};

#endif // TUTORIAL_VULKAN_SEMAPHORE
