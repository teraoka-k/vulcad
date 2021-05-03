#if !defined(TUTORIAL_WINDOW_WINDOW)
#define TUTORIAL_WINDOW_WINDOW

#include <GLFW/glfw3.h>

class Window {
private:
  inline static GLFWwindow *window = NULL;

public:
  static void init(uint32_t width = 800, uint32_t height = 400) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Window::window =
        glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

    Window::render();
  }

  static void kill() {
    glfwDestroyWindow(Window::window);
    glfwTerminate();
  }

private:
  static void render() {
    while (!glfwWindowShouldClose(Window::window)) {
      glfwPollEvents();
    }
  }
};

#endif // TUTORIAL_WINDOW_WINDOW