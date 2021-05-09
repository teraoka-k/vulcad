#if !defined(TUTORIAL_APP)
#define TUTORIAL_APP

#include <vulkan/vulkan.h>

#include "vulkan/debugMessenger.cc"
#include "vulkan/deviceQueue.cc"
#include "vulkan/instance.cc"
#include "vulkan/logicalDevice.cc"
#include "vulkan/physicalDevice.cc"
#include "vulkan/windowSurface.cc"
#include "window/window.cc"

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

    // main loop
    window.render(vkDevice, physicalDevice, windowSurface.vkSurface,
                  window.glfwWindow, graphicsQueue, presentQueue);

    // release memory before exit
    logicalDevice.kill();
    if (enablesValidationLayer)
      debugMessenger.kill(vkInstance);
    window.kill();
    windowSurface.kill(vkInstance);
    instance.kill();
  }
};

#endif // TUTORIAL_APP