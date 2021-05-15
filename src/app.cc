#if !defined(TUTORIAL_APP)
#define TUTORIAL_APP

#include <vulkan/vulkan.h>

#include "vulkan/debugMessenger.cc"
#include "vulkan/device/logicalDevice.cc"
#include "vulkan/device/physicalDevice.cc"
#include "vulkan/instance.cc"
#include "vulkan/window/surface.cc"
#include "vulkan/window/window.cc"

class App {

public:
  static void run() {
    // setup
    auto window = Window(800, 600);
    auto instance = Instance();
    auto vkInstance = instance.vkInstance;
    auto surface = Surface(vkInstance, window.glfwWindow);
    auto debugMessenger =
        enablesValidationLayer ? DebugMessenger(vkInstance) : NULL;
    auto physicalDevice = PhysicalDevice(vkInstance, surface.vkSurface);
    auto logicalDevice = LogicalDevice(physicalDevice);
    auto vkDevice = logicalDevice.vkDevice;

    // main loop
    window.render(vkDevice, physicalDevice, surface.vkSurface,
                  window.glfwWindow);

    // release memory before exit
    logicalDevice.kill();
    if (enablesValidationLayer)
      debugMessenger.kill(vkInstance);
    window.kill();
    surface.kill(vkInstance);
    instance.kill();
  }
};

#endif // TUTORIAL_APP