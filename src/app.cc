#if !defined(TUTORIAL_APP)
#define TUTORIAL_APP

#include <vulkan/vulkan.h>

#include "vulkan/command/commandBuffer.cc"
#include "vulkan/command/commandPool.cc"
#include "vulkan/debugMessenger.cc"
#include "vulkan/deviceQueue.cc"
#include "vulkan/framebuffer.cc"
#include "vulkan/imageView.cc"
#include "vulkan/instance.cc"
#include "vulkan/logicalDevice.cc"
#include "vulkan/physicalDevice.cc"
#include "vulkan/pipeline/pipeline.cc"
#include "vulkan/semaphoreAndFence.cc"
#include "vulkan/swapChain.cc"
#include "vulkan/windowSurface.cc"
#include "window/window.cc"
#include <iostream>
#include <vector>

class App {

public:
  static void run() {
    // setup
    auto window = Window(800, 600);
    auto instance = Instance();
    auto vkInstance = instance.vkInstance;
    auto windowSurface = WindowSurface(vkInstance, window.glfwWindow);
    auto debugMessenger =
        enablesValidationLayer ? DebugMessenger(vkInstance) : NULL;
    auto physicalDevice = PhysicalDevice(vkInstance, windowSurface.vkSurface);
    auto logicalDevice = LogicalDevice(physicalDevice);
    auto vkDevice = logicalDevice.vkDevice;
    auto [graphicsQueue, presentQueue] =
        DeviceQueue::get(vkDevice, physicalDevice.queueFamilyIndices);
    auto swapChain = SwapChain(physicalDevice.vkPhysicalDevice,
                               physicalDevice.queueFamilyIndices, vkDevice,
                               windowSurface.vkSurface, window.glfwWindow);
    auto imageView = ImageView(vkDevice, swapChain);
    auto pipeline = Pipeline(vkDevice, swapChain.format, swapChain.extent);
    auto framebuffer = Framebuffer(imageView.swapChainImageViews,
                                   pipeline.renderPass.vkRenderPass,
                                   swapChain.extent, vkDevice);
    auto commandPool = CommandPool(physicalDevice.queueFamilyIndices, vkDevice);
    auto commandBuffer =
        CommandBuffer(framebuffer.swapChainFramebuffers,
                      commandPool.vkCommandPool, vkDevice, swapChain.extent,
                      pipeline.renderPass.vkRenderPass, pipeline.vkPipeline);
    auto semaphoreAndFence =
        SemaphoreAndFence(vkDevice, imageView.swapChainImageViews.size());

    // main loop
    window.render(vkDevice, swapChain.vkSwapChain, semaphoreAndFence,
                  commandBuffer.commandBuffers, graphicsQueue, presentQueue);

    // release memory before exit
    semaphoreAndFence.kill(vkDevice);
    commandPool.kill(vkDevice);
    framebuffer.kill(vkDevice);
    pipeline.kill(vkDevice);
    imageView.kill(vkDevice);
    swapChain.kill(vkDevice);
    logicalDevice.kill();
    if (enablesValidationLayer)
      debugMessenger.kill(vkInstance);
    window.kill();
    windowSurface.kill(vkInstance);
    instance.kill();
  }
};

#endif // TUTORIAL_APP