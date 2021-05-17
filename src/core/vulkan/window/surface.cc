#if !defined(VULCAD_CORE_VULKAN_WINDOW_SURFACE)
#define VULCAD_CORE_VULKAN_WINDOW_SURFACE

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class Surface {

public:
  VkSurfaceKHR vkSurface;

  Surface(VkInstance instance, GLFWwindow *glfwWindow) {
    if (glfwCreateWindowSurface(instance, glfwWindow, nullptr,
                                &this->vkSurface) != VK_SUCCESS)
      throw std::runtime_error("failed to create window surface!");
  }

  void kill(VkInstance instance) {
    vkDestroySurfaceKHR(instance, this->vkSurface, nullptr);
  }
};

#endif // VULCAD_CORE_VULKAN_WINDOW_SURFACE
