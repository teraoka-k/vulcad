#if !defined(TUTORIAL_APP)
#define TUTORIAL_APP

#include <vulkan/vulkan.h>

#include "vulkan/debugMessenger.cc"
#include "vulkan/instance.cc"
#include "vulkan/logicalDevice.cc"
#include "vulkan/physicalDevice.cc"
#include "window/window.cc"
#include <iostream>
#include <vector>

class App {
public:
  static void run() {
    auto instance = Instance::init();
    DebugMessenger::init(instance);
    auto physicalDevice = PhysicalDevice(instance);
    LogicalDevice::init(physicalDevice);

    Window::init(1024, 768);

    LogicalDevice::kill();
    if (enablesValidationLayer)
      DebugMessenger::kill(instance);
    Window::kill();
    Instance::kill();
  }
};

#endif // TUTORIAL_APP