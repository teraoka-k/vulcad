#if !defined(VULCAD_CORE_VULKAN_INSTANCE)
#define VULCAD_CORE_VULKAN_INSTANCE

#include "layer.cc"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vulkan/vulkan.h>

class Instance {

public:
  VkInstance vkInstance;

  Instance() {
    auto createInfo = Instance::createCreateInfo();

    auto appInfo = Instance::createAppInfo();
    createInfo.pApplicationInfo = &appInfo;

    auto layers = Layer::getLayers();
    createInfo.enabledLayerCount = layers.size();
    createInfo.ppEnabledLayerNames = layers.data();
    auto extensions = Layer::getRequiredExtensions();
    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (vkCreateInstance(&createInfo, NULL, &this->vkInstance) != VK_SUCCESS)
      throw std::runtime_error("failed to create instance!");
  }

  void kill() { vkDestroyInstance(this->vkInstance, nullptr); }

private:
  static VkApplicationInfo createAppInfo() {
    return VkApplicationInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Tutorial",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };
  }

  static VkInstanceCreateInfo createCreateInfo() {
    uint32_t glfwExtensionCount = 0;
    auto createInfo = VkInstanceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames =
            glfwGetRequiredInstanceExtensions(&glfwExtensionCount),
    };
    return createInfo;
  }
};
#endif // VULCAD_CORE_VULKAN_INSTANCE
