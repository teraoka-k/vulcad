#if !defined(TUTORIAL_VULKAN_PIPELINE_RENDER_PASS)
#define TUTORIAL_VULKAN_PIPELINE_RENDER_PASS

#include <vulkan/vulkan.h>

class RenderPass {

public:
  VkRenderPass vkRenderPass;

  RenderPass() {} // only to use this instance as class member variable
  RenderPass(VkFormat format, VkDevice device) {
    auto attachmentDescription = this->getAttachmentDescription(format);
    auto attachmentReference = this->getAttachmentReference();
    auto subpassDescription = this->getSubpassDescreption(attachmentReference);
    auto createInfo =
        this->getCreateInfo(attachmentDescription, subpassDescription);
    if (vkCreateRenderPass(device, &createInfo, nullptr, &this->vkRenderPass) !=
        VK_SUCCESS)
      throw std::runtime_error("failed to create render pass!");
  }

  void kill(VkDevice device) {
    vkDestroyRenderPass(device, this->vkRenderPass, nullptr);
  }

private:
  VkAttachmentDescription getAttachmentDescription(VkFormat format) {
    return {
        .format = format,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };
  }

  VkAttachmentReference getAttachmentReference() {
    return {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
    };
  }

  VkRenderPassCreateInfo
  getCreateInfo(VkAttachmentDescription &attachmentDescription,
                VkSubpassDescription &subpassDescription) {
    return {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &attachmentDescription,
        .subpassCount = 1,
        .pSubpasses = &subpassDescription,
    };
  }

  VkSubpassDescription
  getSubpassDescreption(VkAttachmentReference &attachmentReference) {
    return {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = 1,
        .pColorAttachments = &attachmentReference,
    };
  }
};

#endif // TUTORIAL_VULKAN_PIPELINE_RENDER_PASS
