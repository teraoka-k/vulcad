#if !defined(TUTORIAL_VULKAN_PIPELINE_PIPELINE)
#define TUTORIAL_VULKAN_PIPELINE_PIPELINE

#include "../../util/readFile.cc"
#include "fixedFunctions/colorBlend.cc"
#include "fixedFunctions/inputAssembly.cc"
#include "fixedFunctions/multisample.cc"
#include "fixedFunctions/rasterization.cc"
#include "fixedFunctions/vertexInput.cc"
#include "fixedFunctions/viewport.cc"
#include "pipelineLayout.cc"
#include "renderPass.cc"
#include "shaderStage.cc"
#include <string>
#include <vulkan/vulkan.h>

class Pipeline {
  ShaderStage shaderStage;

public:
  PipelineLayout layout;
  RenderPass renderPass;
  VkPipeline vkPipeline;

  Pipeline() {}
  Pipeline(VkDevice device, VkFormat format, VkExtent2D extent2D) {
    this->shaderStage = ShaderStage(device);
    this->layout = PipelineLayout(device);
    this->renderPass = RenderPass(format, device);

    VkPipelineShaderStageCreateInfo shaderStages[] = {
        this->shaderStage.vertShaderStageCreateInfo,
        this->shaderStage.fragShaderStageCreateInfo};

    auto vertexInput = VertexInput::getCreateInfo();
    auto inputAssembly = InputAssembly::getCreateInfo();
    auto viewport = Viewport::getCreateInfo(extent2D);
    auto rasterization = Rasterization::getCreateInfo();
    auto multisample = Multisample::getCreateInfo();
    auto colorBlend = ColorBlend::getCreateInfo();
    VkGraphicsPipelineCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = 2,
        .pStages = shaderStages,
        .pVertexInputState = &vertexInput,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewport,
        .pRasterizationState = &rasterization,
        .pMultisampleState = &multisample,
        .pDepthStencilState = nullptr,
        .pColorBlendState = &colorBlend,
        .pDynamicState = nullptr,
        .layout = this->layout.vkPipelineLayout,
        .renderPass = this->renderPass.vkRenderPass,
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1,
    };

    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &createInfo,
                                  nullptr, &this->vkPipeline) != VK_SUCCESS)
      throw std::runtime_error("failed to create graphics pipeline!");
  }

  void kill(VkDevice device) {
    vkDestroyPipeline(device, this->vkPipeline, nullptr);
    this->renderPass.kill(device);
    this->layout.kill(device);
    this->shaderStage.kill(device);
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_PIPELINE
