#if !defined(TUTORIAL_APP)
#define TUTORIAL_APP

#include <vulkan/vulkan.h>

#include "vulkan/instance.cc"
#include "window/window.cc"
#include <iostream>
#include <vector>

class App {

public:
  void run() {
    auto vkInstance = initVkInstance();
    auto window = Window(1024, 768);
    window.start();
    vkDestroyInstance(vkInstance, nullptr);
    window.kill();
  }
};

#endif // TUTORIAL_APP