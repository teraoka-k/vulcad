#if !defined(TUTORIAL_VULKAN_WINDOW_SURFACE)
#define TUTORIAL_VULKAN_WINDOW_SURFACE

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class WindowSurface {

public:
  VkSurfaceKHR vkSurface;

  WindowSurface(VkInstance instance, GLFWwindow *glfwWindow) {
    if (glfwCreateWindowSurface(instance, glfwWindow, nullptr,
                                &this->vkSurface) != VK_SUCCESS)
      throw std::runtime_error("failed to create window surface!");
  }

  void kill(VkInstance instance) {
    vkDestroySurfaceKHR(instance, this->vkSurface, nullptr);
  }
};

#endif // TUTORIAL_VULKAN_WINDOW_SURFACE
