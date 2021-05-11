#if !defined(TUTORIAL_VULKAN_RENDERER)
#define TUTORIAL_VULKAN_RENDERER

#include "command/commandBuffer.cc"
#include "command/commandPool.cc"
#include "framebuffer.cc"
#include "imageView.cc"
#include "physicalDevice.cc"
#include "pipeline/pipeline.cc"
#include "semaphoreAndFence.cc"
#include "swapChain.cc"
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class Renderer {
  CommandBuffer commandBuffer;
  CommandPool commandPool;
  Framebuffer framebuffer;
  size_t frameIndex = 0;
  ImageView imageView;
  Pipeline pipeline;
  SemaphoreAndFence semaphoreAndFence;
  SwapChain swapChain;
  VkQueue graphicsQueue;
  VkQueue presentQueue;

public:
  Renderer(VkDevice device, PhysicalDevice physicalDevice, VkSurfaceKHR surface,
           GLFWwindow *window) {
    auto [graphicsQueue, presentQueue] =
        DeviceQueue::get(device, physicalDevice.queueFamilyIndices);
    this->graphicsQueue = graphicsQueue;
    this->presentQueue = presentQueue;
    this->commandPool = CommandPool(physicalDevice.queueFamilyIndices, device);
    this->createSwapChain(device, physicalDevice, surface, window);
    this->semaphoreAndFence =
        SemaphoreAndFence(device, this->imageView.swapChainImageViews.size());
  }

  /**
   * [async function]
   *  queue commands for GPU to draw frames
   *  and return before GPU finishes commands
   */
  void drawFrame(VkDevice device, PhysicalDevice physicalDevice,
                 VkSurfaceKHR surface, GLFWwindow *window) {
    auto &imageState = this->semaphoreAndFence.images[this->frameIndex];
    vkWaitForFences(device, 1, &imageState.isInUse, VK_TRUE, UINT64_MAX);
    uint32_t imageIndex;

    auto result = vkAcquireNextImageKHR(device, this->swapChain.vkSwapChain,
                                        UINT64_MAX / 2, imageState.exists,
                                        VK_NULL_HANDLE, &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
      return this->recreateSwapChain(device, physicalDevice, surface, window);
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
      throw std::runtime_error("failed to acquire swap chain image!");

    vkResetFences(device, 1, &imageState.isInUse);
    this->queueSubmit(imageState,
                      &this->commandBuffer.commandBuffers[imageIndex]);

    result = this->queuePresent(&this->swapChain.vkSwapChain,
                                &imageState.isReadyToPresent, &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
      return this->recreateSwapChain(device, physicalDevice, surface, window);
    else if (result != VK_SUCCESS)
      throw std::runtime_error("failed to present swap chain image!");

    this->frameIndex = (this->frameIndex + 1) % semaphoreAndFence.images.size();
  }

  void kill(VkDevice device) {
    this->semaphoreAndFence.kill(device);
    this->commandBuffer.kill(device);
    this->commandPool.kill(device);
    this->framebuffer.kill(device);
    this->pipeline.kill(device);
    this->imageView.kill(device);
    this->swapChain.kill(device);
  }

  void recreateSwapChain(VkDevice device, PhysicalDevice physicalDevice,
                         VkSurfaceKHR surface, GLFWwindow *window) {
    vkDeviceWaitIdle(device);
    this->commandBuffer.free(device, this->commandPool.vkCommandPool);
    this->framebuffer.kill(device);
    this->pipeline.kill(device);
    this->imageView.kill(device);
    this->swapChain.kill(device);
    this->createSwapChain(device, physicalDevice, surface, window);
  }

private:
  void createSwapChain(VkDevice device, PhysicalDevice physicalDevice,
                       VkSurfaceKHR surface, GLFWwindow *window) {
    this->swapChain =
        SwapChain(physicalDevice.vkPhysicalDevice,
                  physicalDevice.queueFamilyIndices, device, surface, window);
    this->imageView = ImageView(device, this->swapChain);
    this->pipeline =
        Pipeline(device, this->swapChain.format, this->swapChain.extent);
    this->framebuffer = Framebuffer(this->imageView.swapChainImageViews,
                                    this->pipeline.renderPass.vkRenderPass,
                                    this->swapChain.extent, device);
    this->commandBuffer = CommandBuffer(
        this->framebuffer.swapChainFramebuffers,
        this->commandPool.vkCommandPool, device, this->swapChain.extent,
        this->pipeline.renderPass.vkRenderPass, this->pipeline.vkPipeline,
        physicalDevice, this->graphicsQueue);
  }

  VkResult queuePresent(VkSwapchainKHR *swapChain, VkSemaphore *pWaitSemaphore,
                        uint *imageIndex) {
    VkPresentInfoKHR presentInfo = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = pWaitSemaphore,
        .swapchainCount = 1,
        .pSwapchains = swapChain,
        .pImageIndices = imageIndex,
        .pResults = nullptr,
    };
    return vkQueuePresentKHR(this->presentQueue, &presentInfo);
  }

  void queueSubmit(imageState &imageState, VkCommandBuffer *commandBuffer) {
    VkPipelineStageFlags waitDstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &imageState.exists,
        .pWaitDstStageMask = &waitDstStageMask,
        .commandBufferCount = 1,
        .pCommandBuffers = commandBuffer,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &imageState.isReadyToPresent,
    };
    if (vkQueueSubmit(this->graphicsQueue, 1, &submitInfo,
                      imageState.isInUse) != VK_SUCCESS)
      throw std::runtime_error("failed to submit draw command buffer!");
  }
};

#endif // TUTORIAL_VULKAN_RENDERER
