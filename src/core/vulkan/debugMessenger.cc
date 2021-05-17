#if !defined(VULCAD_CORE_VULKAN_DEBUG_MESSENGER)
#define VULCAD_CORE_VULKAN_DEBUG_MESSENGER

#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.h>

class DebugMessenger {

  VkDebugUtilsMessengerEXT messenger = {};

public:
  DebugMessenger(VkInstance instance) {
    auto createInfo = VkDebugUtilsMessengerCreateInfoEXT{
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = DebugMessenger::print,
    };

    auto vkCreateDebugUtilsMessengerEXT =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkCreateDebugUtilsMessengerEXT");
    if (vkCreateDebugUtilsMessengerEXT == nullptr ||
        vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr,
                                       &this->messenger) != VK_SUCCESS)
      throw std::runtime_error("failed to set up debug messenger");
  }

  void kill(VkInstance instance) {
    auto vkDestroyDebugUtilsMessengerEXT =
        (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkDestroyDebugUtilsMessengerEXT");
    if (vkDestroyDebugUtilsMessengerEXT != nullptr)
      vkDestroyDebugUtilsMessengerEXT(instance, this->messenger, nullptr);
  }

private:
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  print(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData) {
    std::cerr << "\n-----validation layer start-----\n"
              << pCallbackData->pMessage << "\n-----validation layer end-----\n"
              << std::endl;
    return VK_FALSE;
  }
};

#endif // VULCAD_CORE_VULKAN_DEBUG_MESSENGER
