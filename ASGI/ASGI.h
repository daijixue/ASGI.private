#pragma once
#include "ASGI.hpp"

namespace ASGI {
	ASGI_API graphics_context_ptr CreateContext(GIType driver, SwapchainCreateInfo* swapchainInfo = nullptr, const char* device_name = nullptr);
	ASGI_API void SetCurrentContext(GraphicsContext* context);
	//
	ASGI_API shader_module_ptr CreateShaderModule(const char* shaderPath);
	ASGI_API shader_program_ptr CreateShaderProgram(ShaderModule* pVertexShader, ShaderModule* pGeomteryShader, ShaderModule* pTessControlShader, ShaderModule* pTessEvaluationShader, ShaderModule* pFragmentShader);
	ASGI_API render_pass_ptr CreateRenderPass(const RenderPassCreateInfo& create_info);
	ASGI_API graphics_pipeline_ptr CreateGraphicsPipeline(const GraphicsPipelineCreateInfo& create_info);
	ASGI_API frame_buffer_ptr CreateFrameBuffer(RenderPass* targetRenderPass, uint8_t numAttachment, ImageView** attachments, ClearValue* clearValues, uint32_t width, uint32_t height);
	//
	ASGI_API buffer_ptr CreateBuffer(uint64_t size, BufferUsageFlags usageFlags);
	ASGI_API buffer_update_contex_ptr BeginUpdateBuffer();
	ASGI_API bool EndUpdateBuffer(BufferUpdateContext* pUpdateContext);
	ASGI_API void UpdateBuffer(Buffer* pbuffer, uint32_t offset, uint32_t size, void* pdata, BufferUpdateContext* pUpdateContext = nullptr);
	ASGI_API void* MapBuffer(Buffer* pbuffer, uint32_t offset, uint32_t size, MapMode mapMode = MapMode::MAP_MODE_WRITE);
	ASGI_API void UnMapBuffer(Buffer* pbuffer);
	ASGI_API void BindUniformBuffer(ShaderProgram* pProgram, uint8_t setIndex, uint32_t bindingIndex, Buffer* pbuffer, uint32_t offset, uint32_t size);
	//
	ASGI_API image_2d_ptr CreateImage2D(uint32_t sizeX, uint32_t sizeY, Format format, uint32_t numMips, SampleCountFlagBits samples, ImageUsageFlags usageFlags);
	ASGI_API image_view_ptr CreateImageView(Image2D* srcImage, uint32_t mipLevel);
	ASGI_API image_view_ptr CreateImageView(Image2D* srcImage, uint32_t mipLevel, uint32_t numMipLevels, Format format);

	ASGI_API sampler_ptr CreateSampler(float minLod = 0.0f, float maxLod = 0.0f, float  mipLodBias = 0.0f,
		Filter magFilter = Filter::FILTER_LINEAR, Filter minFilter = Filter::FILTER_LINEAR,
		SamplerMipmapMode mipmapMode = SamplerMipmapMode::SAMPLER_MIPMAP_MODE_LINEAR,
		SamplerAddressMode addressModeU = SamplerAddressMode::SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		SamplerAddressMode addressModeV = SamplerAddressMode::SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		SamplerAddressMode addressModeW = SamplerAddressMode::SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		float  maxAnisotropy = 1.0f, CompareOp compareOp = CompareOp::COMPARE_OP_NEVER,
		BorderColor borderColor = BorderColor::BORDER_COLOR_INT_OPAQUE_WHITE);

	ASGI_API void BindTexture(ShaderProgram* pProgram, uint8_t setIndex, uint32_t bindingIndex, ImageView* pImgView, Sampler* pSampler);
	ASGI_API image_update_context_ptr BeginUpdateImage();
	ASGI_API bool EndUpdateImage(ImageUpdateContext* pUpdateContext);
	ASGI_API bool UpdateImage2D(Image2D* pimg, uint32_t level, uint32_t offsetX, uint32_t offsetY, uint32_t sizeX, uint32_t sizeY, void* pdata, ImageUpdateContext* pUpdateContext = nullptr);

	ASGI_API ExcuteQueue* AcquireExcuteQueue(QueueType queueType);
	ASGI_API void WaitQueueExcuteFinished(uint32_t numWaiteQueue, ExcuteQueue** excuteQueues);
	ASGI_API bool SubmitCommands(ExcuteQueue* excuteQueue, uint32_t numBuffers, CommandBuffer** cmdBuffers, uint32_t numWaiteQueue, ExcuteQueue** waiteQueues, uint32_t numSwapchain, Swapchain** waiteSwapchains, bool waiteFinished = false);
	ASGI_API void Present(ExcuteQueue* excuteQueue, uint32_t numSwapchain, Swapchain** swapchains, bool waiteFinished = false);

	ASGI_API command_buffer_ptr CreateCmdBuffer();
	ASGI_API void BeginCmdBuffer(CommandBuffer* cmdBuffer);
	ASGI_API void EndCmdBuffer(CommandBuffer* cmdBuffer);
	ASGI_API bool BeginRenderPass(CommandBuffer* cmdBuffer, RenderPass* renderPass, FrameBuffer* frameBuffer);
	ASGI_API void EndSubRenderPass(CommandBuffer* cmdBuffer, RenderPass* renderPass, uint32_t numSecondCmdBuffer, CommandBuffer** secondCmdBuffers);
	ASGI_API void EndRenderPass(CommandBuffer* cmdBuffer, RenderPass* renderPass, uint32_t numSecondCmdBuffer, CommandBuffer** secondCmdBuffers);
	ASGI_API bool BeginComputePass(CommandBuffer* cmdBuffer, ComputePass* computePass);
	ASGI_API void EndComputePass(CommandBuffer* cmdBuffer, ComputePass* computePass, uint32_t numSecondCmdBuffer, CommandBuffer** secondCmdBuffers);

	ASGI_API void CmdBindPipeline(CommandBuffer*  cmdBuffer, GraphicsPipeline* pipeline);
	ASGI_API void CmdSetViewport(CommandBuffer*  cmdBuffer, uint32_t   firstViewport, uint32_t  viewportCount, Viewport*  pViewports);
	ASGI_API void CmdSetScissor(CommandBuffer*  cmdBuffer, uint32_t  firstScissor, uint32_t   scissorCount, Rect2D*  pScissors);
	ASGI_API void CmdSetLineWidth(CommandBuffer*  cmdBuffer, float   lineWidth);
	ASGI_API void CmdBindIndexBuffer(CommandBuffer* cmdBuffer, Buffer* pBuffer, uint32_t offset, Format indexFormat);
	ASGI_API void CmdBindVertexBuffer(CommandBuffer* cmdBuffer, uint32_t  bindingIndex, Buffer*  pBuffer, uint32_t offset);
	ASGI_API void CmdDraw(CommandBuffer* cmdBuffer, uint32_t vertexCount, uint32_t  instanceCount, uint32_t firstVertex, uint32_t  firstInstance);
	ASGI_API void CmdDrawIndexed(CommandBuffer* cmdBuffer, uint32_t indexCount, uint32_t   instanceCount, uint32_t  firstIndex, int32_t  vertexOffset, uint32_t  firstInstance);
}
