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
#include <glm/glm.hpp>

class App {

public:
  /**
   * @param vertices
   * @param indices specify 3 vertices for each triangle
   * @param width of window
   * @param height of window
   * @param model for MVP matrix's M
   */
  static void run(std::vector<vulcad::Vertex> vertices,
                  std::vector<uint16_t> indices, uint16_t width,
                  uint16_t height, glm::mat4 model) {
    // setup
    auto window = Window(width, height);
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
                  window.glfwWindow, vertices, indices, model);

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