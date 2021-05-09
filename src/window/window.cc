#if !defined(TUTORIAL_WINDOW_WINDOW)
#define TUTORIAL_WINDOW_WINDOW

#include "../vulkan/renderer.cc"
#include "../vulkan/semaphoreAndFence.cc"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <vulkan/vulkan.h>

class Window {
public:
  GLFWwindow *glfwWindow = NULL;

  Window(uint32_t width = 800, uint32_t height = 400) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    this->glfwWindow =
        glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
  }

  void kill() {
    glfwDestroyWindow(this->glfwWindow);
    glfwTerminate();
  }

  void render(VkDevice device, PhysicalDevice physicalDevice,
              VkSurfaceKHR surface, GLFWwindow *window, VkQueue graphicsQueue,
              VkQueue presentQueue) {
    auto renderer = Renderer(device, physicalDevice, surface, window);
    while (!glfwWindowShouldClose(this->glfwWindow)) {
      glfwPollEvents();
      renderer.drawFrame(device, physicalDevice, surface, window, graphicsQueue,
                         presentQueue);
    }
    vkDeviceWaitIdle(device);
    renderer.kill(device);
  }
};

#endif // TUTORIAL_WINDOW_WINDOW