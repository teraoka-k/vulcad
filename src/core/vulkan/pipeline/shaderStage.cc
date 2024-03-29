#if !defined(VULCAD_CORE_VULKAN_SHADER_STAGE)
#define VULCAD_CORE_VULKAN_SHADER_STAGE

#include <vulkan/vulkan.h>

const std::string SHADER_DIR = "shaders/";

class ShaderStage {
  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;

public:
  VkPipelineShaderStageCreateInfo vertShaderStageCreateInfo;
  VkPipelineShaderStageCreateInfo fragShaderStageCreateInfo;

  ShaderStage(VkDevice device) {
    this->vertShaderStageCreateInfo = this->getShaderStageCreateInfo(
        VK_SHADER_STAGE_VERTEX_BIT,
        (this->vertShaderModule =
             this->createShaderModule(device, "vert.spv")));
    this->fragShaderStageCreateInfo = this->getShaderStageCreateInfo(
        VK_SHADER_STAGE_FRAGMENT_BIT,
        (this->fragShaderModule =
             this->createShaderModule(device, "frag.spv")));
  }
  // only to use ShaderStage as class member variable of another class
  ShaderStage() {}

  void kill(VkDevice device) {
    vkDestroyShaderModule(device, this->fragShaderModule, nullptr);
    vkDestroyShaderModule(device, this->vertShaderModule, nullptr);
  }

private:
  VkShaderModule createShaderModule(VkDevice device, std::string fileName) {
    auto code = readFile(SHADER_DIR + fileName);
    auto createInfo = VkShaderModuleCreateInfo{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = code.size(),
        .pCode = reinterpret_cast<const uint32_t *>(code.data()),
    };
    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to create shader module");
    return shaderModule;
  }

  VkPipelineShaderStageCreateInfo
  getShaderStageCreateInfo(VkShaderStageFlagBits stage,
                           VkShaderModule shaderModule) {
    return {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = stage,
        .module = shaderModule,
        .pName = "main",
    };
  }
};

#endif // VULCAD_CORE_VULKAN_SHADER_STAGE
