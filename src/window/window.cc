#if !defined(TUTORIAL_WINDOW_WINDOW)
#define TUTORIAL_WINDOW_WINDOW

#include "../vulkan/semaphoreAndFence.cc"
#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan_core.h>

class Window {

public:
  GLFWwindow *glfwWindow = NULL;

  Window(uint32_t width = 800, uint32_t height = 400) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->glfwWindow =
        glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
  }

  void kill() {
    glfwDestroyWindow(this->glfwWindow);
    glfwTerminate();
  }

  void render(VkDevice device, VkSwapchainKHR swapChain,
              SemaphoreAndFence semaphoreAndFence,
              std::vector<VkCommandBuffer> commandBuffers,
              VkQueue graphicsQueue, VkQueue presentQueue) {
    while (!glfwWindowShouldClose(this->glfwWindow)) {
      glfwPollEvents();
      this->drawFrame(device, swapChain, semaphoreAndFence, commandBuffers,
                      graphicsQueue, presentQueue);
    }
    vkDeviceWaitIdle(device);
  }

private:
  size_t frameIndex = 0;
  /**
   * [async function]
   *  queue commands for GPU to draw frames
   *  and return before GPU finishes commands
   */
  void drawFrame(VkDevice device, VkSwapchainKHR swapChain,
                 SemaphoreAndFence semaphoreAndFence,
                 std::vector<VkCommandBuffer> commandBuffers,
                 VkQueue graphicsQueue, VkQueue presentQueue) {
    auto &imageState = semaphoreAndFence.images[this->frameIndex];
    vkWaitForFences(device, 1, &imageState.isInUse, VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, &imageState.isInUse);
    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, swapChain, UINT64_MAX / 2,
                          imageState.isReadyToRender, VK_NULL_HANDLE,
                          &imageIndex);
    this->queueSubmit(imageState, &commandBuffers[imageIndex], graphicsQueue);
    this->queuePresent(&swapChain, &imageState.finishedRendering, &imageIndex,
                       presentQueue);
    this->frameIndex = (this->frameIndex + 1) % semaphoreAndFence.images.size();
  }

  void queueSubmit(imageState &imageState, VkCommandBuffer *commandBuffer,
                   VkQueue graphicsQueue) {
    VkPipelineStageFlags waitDstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &imageState.isReadyToRender,
        .pWaitDstStageMask = &waitDstStageMask,
        .commandBufferCount = 1,
        .pCommandBuffers = commandBuffer,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &imageState.finishedRendering,
    };
    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, imageState.isInUse) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to submit draw command buffer!");
  }

  void queuePresent(VkSwapchainKHR *swapChain, VkSemaphore *pWaitSemaphore,
                    uint *imageIndex, VkQueue presentQueue) {
    VkPresentInfoKHR presentInfo = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = pWaitSemaphore,
        .swapchainCount = 1,
        .pSwapchains = swapChain,
        .pImageIndices = imageIndex,
        .pResults = nullptr,
    };
    vkQueuePresentKHR(presentQueue, &presentInfo);
  }
};

#endif // TUTORIAL_WINDOW_WINDOW