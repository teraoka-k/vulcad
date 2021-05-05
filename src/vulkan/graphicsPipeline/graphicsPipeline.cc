#if !defined(TUTORIAL_VULKAN_GRAPHICS_PIPELINE_GRAPHICS_PIPELINE)
#define TUTORIAL_VULKAN_GRAPHICS_PIPELINE_GRAPHICS_PIPELINE

#include "../../util/readFile.cc"
#include <string>
#include <vulkan/vulkan.h>

const std::string SHADER_DIR = "shaders/";

class GraphicsPipeline {
  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;

public:
  GraphicsPipeline(VkDevice device) {
    auto vertShaderStageInfo = this->getShaderStageCreateInfo(
        VK_SHADER_STAGE_VERTEX_BIT,
        (this->vertShaderModule =
             this->createShaderModule(device, "vert.spv")));
    auto fragShaderStageInfo = this->getShaderStageCreateInfo(
        VK_SHADER_STAGE_FRAGMENT_BIT,
        (this->fragShaderModule =
             this->createShaderModule(device, "frag.spv")));

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo,
                                                      fragShaderStageInfo};
  }

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

#endif // TUTORIAL_VULKAN_GRAPHICS_PIPELINE_GRAPHICS_PIPELINE
