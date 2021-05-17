#if !defined(VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_COLOR_BLEND)
#define VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_COLOR_BLEND

#include <vulkan/vulkan.h>

class ColorBlend {
  // store the variable in static memory to avoid segmentation faults
  inline static VkPipelineColorBlendAttachmentState attachment = {};

public:
  static VkPipelineColorBlendStateCreateInfo getCreateInfo() {
    ColorBlend::attachment = {
        .blendEnable = VK_FALSE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };

    auto createInfo = VkPipelineColorBlendStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments = &ColorBlend::attachment,
    };
    createInfo.blendConstants[0] = 0.0f;
    createInfo.blendConstants[1] = 0.0f;
    createInfo.blendConstants[2] = 0.0f;
    createInfo.blendConstants[3] = 0.0f;
    return createInfo;
  }
};

#endif // VULCAD_CORE_VULKAN_PIPELINE_FIXED_FUNCTIONS_COLOR_BLEND
