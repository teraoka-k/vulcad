#if !defined(TUTORIAL_WINDOW_WINDOW)
#define TUTORIAL_WINDOW_WINDOW

#include <GLFW/glfw3.h>

class Window {
private:
  GLFWwindow *window;

public:
  Window(uint32_t width = 800, uint32_t height = 400) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
  }

  void kill() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
  }

  void start() {
    while (!glfwWindowShouldClose(this->window)) {
      glfwPollEvents();
    }
  }
};

#endif // TUTORIAL_WINDOW_WINDOW