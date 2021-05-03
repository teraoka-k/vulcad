#if !defined(TUTORIAL_VULKAN_DEBUG_MESSENGER)
#define TUTORIAL_VULKAN_DEBUG_MESSENGER

#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.h>

class DebugMessenger {

  inline static VkDebugUtilsMessengerEXT messenger = {};

public:
  static void kill(VkInstance instance) {
    auto vkDestroyDebugUtilsMessengerEXT =
        (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkDestroyDebugUtilsMessengerEXT");
    if (vkDestroyDebugUtilsMessengerEXT != nullptr)
      vkDestroyDebugUtilsMessengerEXT(instance, DebugMessenger::messenger,
                                      nullptr);
  }

  static void init(VkInstance instance) {
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
                                       &DebugMessenger::messenger) !=
            VK_SUCCESS)
      throw std::runtime_error("failed to set up debug messenger");
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

#endif // TUTORIAL_VULKAN_DEBUG_MESSENGER
