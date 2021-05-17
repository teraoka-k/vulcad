#if !defined(VULCAD_CORE_APP)
#define VULCAD_CORE_APP

#include <vulkan/vulkan.h>

#include "../vulcad.h"
#include "vulkan/debugMessenger.cc"
#include "vulkan/device/logicalDevice.cc"
#include "vulkan/device/physicalDevice.cc"
#include "vulkan/instance.cc"
#include "vulkan/window/surface.cc"
#include "vulkan/window/window.cc"

class App {

public:
  static void
  run(std::vector<vulcad::Vertex> vertices = {{{-.5, -.5, 0}, {1, 0, 0}},
                                              {{.5, -.5, 0}, {0, 1, 0}},
                                              {{.5, .5, 0}, {0, 0, 1}},
                                              {{-.5, .5, 0}, {1, 1, 1}}},
      std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0}) {
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
                  window.glfwWindow, vertices, indices);

    // release memory before exit
    logicalDevice.kill();
    if (enablesValidationLayer)
      debugMessenger.kill(vkInstance);
    window.kill();
    surface.kill(vkInstance);
    instance.kill();
  }
};

#endif // VULCAD_CORE_APP