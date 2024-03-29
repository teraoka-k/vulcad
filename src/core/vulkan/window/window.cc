#if !defined(VULCAD_CORE_WINDOW_WINDOW)
#define VULCAD_CORE_WINDOW_WINDOW

#include "../../../vulcad.h"
#include "../device/queue.cc"
#include "../render/render.cc"
#include "../semaphoreAndFence.cc"
#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>

class Window {
public:
  GLFWwindow *glfwWindow = NULL;

  Window(uint32_t width, uint32_t height) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->glfwWindow =
        glfwCreateWindow(width, height, "VULCAD", nullptr, nullptr);
  }

  void kill() {
    glfwDestroyWindow(this->glfwWindow);
    glfwTerminate();
  }

  void render(VkDevice device, PhysicalDevice physicalDevice,
              VkSurfaceKHR surface, GLFWwindow *window,
              std::vector<vulcad::Vertex> vertices,
              std::vector<uint16_t> indices, glm::mat4 model) {
    auto renderer =
        Renderer(device, physicalDevice, surface, window, vertices, indices);
    while (!glfwWindowShouldClose(this->glfwWindow)) {
      glfwPollEvents();
      renderer.drawFrame(device, physicalDevice, surface, window, model);
    }
    vkDeviceWaitIdle(device);
    renderer.kill(device);
  }
};

#endif // VULCAD_CORE_WINDOW_WINDOW