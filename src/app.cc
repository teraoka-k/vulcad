#if !defined(TUTORIAL_APP)
#define TUTORIAL_APP

#include <vulkan/vulkan.h>

#include "vulkan/debugMessenger.cc"
#include "vulkan/instance.cc"
#include "vulkan/physicalDevice.cc"
#include "window/window.cc"
#include <iostream>
#include <vector>

class App {
public:
  static void run() {
    Instance::init();
    DebugMessenger::run(Instance::instance);
    auto physicalDevice = PhysicalDevice(Instance::instance);

    auto window = Window(1024, 768);
    window.start();

    // if (enablesValidationLayer)
    //   DebugMessenger::kill(Instance::instance);
    window.kill();
    Instance::kill();
  }
};

#endif // TUTORIAL_APP