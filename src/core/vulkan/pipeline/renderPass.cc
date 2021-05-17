#if !defined(VULCAD_CORE_VULKAN_PIPELINE_RENDER_PASS)
#define VULCAD_CORE_VULKAN_PIPELINE_RENDER_PASS

#include <tuple>
#include <vulkan/vulkan.h>

class RenderPass {

public:
  VkRenderPass vkRenderPass;

  RenderPass() {} // only to use this instance as class member variable
  RenderPass(VkFormat format, VkDevice device) {
    auto [attachmentReference, attachmentDescription] =
        this->getAttachment(format);
    auto [subpassDescription, subPassDepencency] =
        this->getSubpass(attachmentReference);
    auto createInfo = this->getCreateInfo(
        &attachmentDescription, &subpassDescription, &subPassDepencency);

    if (vkCreateRenderPass(device, &createInfo, nullptr, &this->vkRenderPass) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to create render pass!");
  }

  void kill(VkDevice device) {
    vkDestroyRenderPass(device, this->vkRenderPass, nullptr);
  }

private:
  std::tuple<VkAttachmentReference, VkAttachmentDescription>
  getAttachment(VkFormat format) {
    return std::make_tuple(
        VkAttachmentReference{
            .attachment = 0,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        },
        VkAttachmentDescription{
            .format = format,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        });
  }

  VkRenderPassCreateInfo
  getCreateInfo(VkAttachmentDescription *attachmentDescription,
                VkSubpassDescription *subpassDescription,
                VkSubpassDependency *subpassDependency) {
    return {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = attachmentDescription,
        .subpassCount = 1,
        .pSubpasses = subpassDescription,
        .dependencyCount = 1,
        .pDependencies = subpassDependency,
    };
  }

  std::tuple<VkSubpassDescription, VkSubpassDependency>
  getSubpass(VkAttachmentReference &attachmentReference) {
    return std::make_tuple(
        VkSubpassDescription{
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = 1,
            .pColorAttachments = &attachmentReference,
        },
        VkSubpassDependency{

            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .dstSubpass = 0,
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask = 0,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,

        });
  }
};

#endif // VULCAD_CORE_VULKAN_PIPELINE_RENDER_PASS
