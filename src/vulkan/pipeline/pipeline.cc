#if !defined(TUTORIAL_VULKAN_PIPELINE_PIPELINE)
#define TUTORIAL_VULKAN_PIPELINE_PIPELINE

#include "../../util/readFile.cc"
#include "pipelineLayout.cc"
#include "renderPass.cc"
#include "shaderStage.cc"
#include <string>
#include <vulkan/vulkan.h>

class Pipeline {

  ShaderStage shaderStage;
  PipelineLayout layout;
  RenderPass renderPass;

public:
  Pipeline(VkDevice device, VkFormat format) {
    this->shaderStage = ShaderStage(device);
    this->layout = PipelineLayout(device);
    this->renderPass = RenderPass(format, device);
  }

  void kill(VkDevice device) {
    this->renderPass.kill(device);
    this->layout.kill(device);
    this->shaderStage.kill(device);
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_PIPELINE
