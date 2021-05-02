#if !defined(TUTORIAL_VULKAN_LAYER)
#define TUTORIAL_VULKAN_LAYER

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string.h>
#include <vector>
#include <vulkan/vulkan.h>

#ifdef NDEBUG
constexpr bool enablesValidationLayer = false;
#else
constexpr bool enablesValidationLayer = true;
#endif

class Layer {
public:
  static std::vector<const char *> getLayers() {
    std::vector<const char *> layers;
    if (enablesValidationLayer)
      layers.push_back("VK_LAYER_KHRONOS_validation");
    Layer::checkIfAllTheLayersSupported(layers);
    return layers;
  }

  static std::vector<const char *> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions,
                                         glfwExtensions + glfwExtensionCount);
    if (enablesValidationLayer)
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    return extensions;
  }

private:
  static void checkIfAllTheLayersSupported(std::vector<const char *> &layers) {
    if (layers.size() == 0)
      return;

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (auto *layerName : layers) {
      for (auto i = 0; i < availableLayers.size(); i++) {
        if (strcmp(layerName, availableLayers[i].layerName) == 0)
          break;
        if (i == availableLayers.size() - 1)
          throw std::runtime_error("layer is not supported: " +
                                   std::string(layerName));
      }
    }
  }
};

#endif // TUTORIAL_VULKAN_LAYER