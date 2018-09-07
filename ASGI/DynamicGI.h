#pragma once

#include "ASGI.hpp"
#include "GPUResource.h"

namespace ASGI {
	class DynamicGI {
	public:
		virtual ~DynamicGI() {}

		virtual bool Init(const char* device_name = nullptr) = 0;
		//graphics pipeline
		virtual ShaderModule* CreateShaderModule(const ShaderModuleCreateInfo& create_info) = 0;
		virtual GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineCreateInfo& create_info) = 0;
		virtual Swapchain* CreateSwapchain(const SwapchainCreateInfo& create_info) = 0;
		//render resource
		virtual VertexBuffer* CreateVertexBuffer(const VertexBufferCreateInfo& create_info) = 0;
		virtual IndexBuffer* CreateIndexBuffer(const IndexBufferCreateInfo& create_info) = 0;
		virtual UniformBuffer* CreateUniformBuffer(const UniformBufferCreateInfo& create_info) = 0;
		virtual Texture2D* CreateTexture2D(const Texture2DCreateInfo& create_info) = 0;
		//render command
		virtual CommandBuffer* CreateCommandBuffer(const CommandBufferCreateInfo& create_info) = 0;
		virtual void CmdSetViewport(CommandBuffer& commandBuffer) = 0;
		virtual void CmdSetScissor(CommandBuffer& commandBuffer) = 0;
		virtual void CmdSetLineWidth(CommandBuffer& commandBuffer) = 0;
		virtual void CmdBindGraphicsPipeline(CommandBuffer& commandBuffer) = 0;
		virtual void CmdBindIndexBuffer(CommandBuffer& commandBuffer) = 0;
		virtual void CmdBindVertexBuffer(CommandBuffer& commandBuffer) = 0;
		virtual void CmdFillBuffer(CommandBuffer& commandBuffer) = 0;
		virtual void CmdUpdateBuffer(CommandBuffer& commandBuffer) = 0;
		virtual void CmdClearColorImage(CommandBuffer& commandBuffer) = 0;
		virtual void CmdClearDepthStencilImage(CommandBuffer& commandBuffer) = 0;
		virtual void CmdDraw(CommandBuffer& commandBuffer) = 0;
		virtual void CmdDrawIndexed(CommandBuffer& commandBuffer) = 0;
	};
}
