// ASGI.cpp : 定义 DLL 应用程序的导出函数。
//
#include "ASGI.h"
#include "VkGLSL.hpp"
#include "VulkanGI.h"

namespace ASGI {
	bool GSupportParallelCommandBuffer = false;
	uint8_t GetFormatSize(Format format) {
		switch (format){
		case Format::FORMAT_R32G32B32A32_SFLOAT:
		case Format::FORMAT_R32G32B32A32_SINT:
		case Format::FORMAT_R32G32B32A32_UINT:
			return 16;
		case Format::FORMAT_R32G32B32_SFLOAT:
		case Format::FORMAT_R32G32B32_SINT:
		case Format::FORMAT_R32G32B32_UINT:
			return 12;
		case Format::FORMAT_R32G32_SFLOAT:
		case Format::FORMAT_R32G32_SINT:
		case Format::FORMAT_R32G32_UINT:
		case Format::FORMAT_R16G16B16A16_SFLOAT:
		case Format::FORMAT_R16G16B16A16_SINT:
		case Format::FORMAT_R16G16B16A16_SNORM:
		case Format::FORMAT_R16G16B16A16_SSCALED:
		case Format::FORMAT_R16G16B16A16_UINT:
		case Format::FORMAT_R16G16B16A16_UNORM:
		case Format::FORMAT_R16G16B16A16_USCALED:
			return 8;
		case Format::FORMAT_R32_SFLOAT:
		case Format::FORMAT_R32_SINT:
		case Format::FORMAT_R32_UINT:
		case Format::FORMAT_R16G16_SFLOAT:
		case Format::FORMAT_R16G16_SINT:
		case Format::FORMAT_R16G16_SNORM:
		case Format::FORMAT_R16G16_SSCALED:
		case Format::FORMAT_R16G16_UINT:
		case Format::FORMAT_R16G16_UNORM:
		case Format::FORMAT_R16G16_USCALED:
		case Format::FORMAT_R8G8B8A8_SINT:
		case Format::FORMAT_R8G8B8A8_SNORM:
		case Format::FORMAT_R8G8B8A8_SRGB:
		case Format::FORMAT_R8G8B8A8_SSCALED:
		case Format::FORMAT_R8G8B8A8_UINT:
		case Format::FORMAT_R8G8B8A8_UNORM:
		case Format::FORMAT_R8G8B8A8_USCALED:
		case Format::FORMAT_B8G8R8A8_SINT:
		case Format::FORMAT_B8G8R8A8_SNORM:
		case Format::FORMAT_B8G8R8A8_SRGB:
		case Format::FORMAT_B8G8R8A8_SSCALED:
		case Format::FORMAT_B8G8R8A8_UINT:
		case Format::FORMAT_B8G8R8A8_UNORM:
		case Format::FORMAT_B8G8R8A8_USCALED:
			return 4;
		case Format::FORMAT_R8G8B8_SINT:
		case Format::FORMAT_R8G8B8_SNORM:
		case Format::FORMAT_R8G8B8_SRGB:
		case Format::FORMAT_R8G8B8_SSCALED:
		case Format::FORMAT_R8G8B8_UINT:
		case Format::FORMAT_R8G8B8_UNORM:
		case Format::FORMAT_R8G8B8_USCALED:
		case Format::FORMAT_B8G8R8_SINT:
		case Format::FORMAT_B8G8R8_SNORM:
		case Format::FORMAT_B8G8R8_SRGB:
		case Format::FORMAT_B8G8R8_SSCALED:
		case Format::FORMAT_B8G8R8_UINT:
		case Format::FORMAT_B8G8R8_UNORM:
		case Format::FORMAT_B8G8R8_USCALED:
			return 3;
		case Format::FORMAT_R16_SFLOAT:
		case Format::FORMAT_R16_SINT:
		case Format::FORMAT_R16_SNORM:
		case Format::FORMAT_R16_SSCALED:
		case Format::FORMAT_R16_UINT:
		case Format::FORMAT_R16_UNORM:
		case Format::FORMAT_R16_USCALED:
		case Format::FORMAT_R8G8_UNORM:
		case Format::FORMAT_R8G8_SNORM:
		case Format::FORMAT_R8G8_USCALED:
		case Format::FORMAT_R8G8_SSCALED:
		case Format::FORMAT_R8G8_UINT:
		case Format::FORMAT_R8G8_SINT:
		case Format::FORMAT_R8G8_SRGB:
			return 2;
		case Format::FORMAT_R8_UNORM:
		case Format::FORMAT_R8_SNORM:
		case Format::FORMAT_R8_USCALED:
		case Format::FORMAT_R8_SSCALED:
		case Format::FORMAT_R8_UINT:
		case Format::FORMAT_R8_SINT:
		case Format::FORMAT_R8_SRGB:
			return 1;
		default :
			return 0;
		}
	}

	DynamicGI* pGI = nullptr;

	bool Init(GIType driver, const char* device_name) {
		if (driver == GIType::GI_VULKAN) {
			pGI = new VulkanGI();
			if (pGI) {
				return pGI->Init(device_name);
			}
			else {
				return false;
			}
		}
		return false;
	}

	ShaderModule* CreateShaderModule(const char* shaderPath) {
		//VKGLSL::GLSLLayout glslLayout;
		//if (!VKGLSL::GLSLLayoutAnalyze(create_info.pcode, glslLayout)) {
		//	return nullptr;
		//}
		//
		std::string spirvPath = std::string(shaderPath) + ".spv";
		std::string spirvCode;
		FILE* pfile = fopen(spirvPath.c_str(), "rb");
		if (pfile == nullptr) {
#ifdef  _WIN32
			char szFilePath[MAX_PATH + 1] = { 0 };
			GetModuleFileName(NULL, szFilePath, MAX_PATH);
			strrchr(szFilePath, '\\')[1] = '\0';
			std::string glslangPath = std::string(szFilePath) + "glslangValidator.exe";
			//
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			ZeroMemory(&pi, sizeof(pi));
			std::string commandLine = glslangPath + " -V " + std::string(shaderPath) + " -o " + spirvPath;
			if (CreateProcess(NULL, (LPSTR)commandLine.c_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
			}
#endif //  _WIN32
			//
			pfile = fopen(spirvPath.c_str(), "rb");
			if (pfile == nullptr) {
				return nullptr;
			}
		}
		//
		fclose(pfile);
		//
		ShaderModuleCreateInfo create_info_spirv;
		create_info_spirv.path = spirvPath.c_str();
		return pGI->CreateShaderModule(create_info_spirv);
	}

	RenderPass* CreateRenderPass(const RenderPassCreateInfo& create_info) {
		return pGI->CreateRenderPass(create_info);
	}

	GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineCreateInfo& create_info) {
		return pGI->CreateGraphicsPipeline(create_info);
	}

	Swapchain* CreateSwapchain(const SwapchainCreateInfo& create_info) {
		return pGI->CreateSwapchain(create_info);
	}

	VertexBuffer* CreateVertexBuffer(uint64_t size, const char* pdata) {
		return pGI->CreateVertexBuffer(size, pdata);
	}

	IndexBuffer* CreateIndexBuffer(uint32_t size, const char* pdata) {
		return pGI->CreateIndexBuffer(size, pdata);
	}

	UniformBuffer* CreateUniformBuffer(uint32_t size, const char* pdata) {
		return pGI->CreateUniformBuffer(size, pdata);
	}

	Texture2D* CreateTexture2D(uint32_t sizeX, uint32_t sizeY, Format format, uint32_t numMips, SampleCountFlagBits samples, ImageUsageFlags usageFlags) {
		return pGI->CreateTexture2D(sizeX, sizeY, format, numMips, samples, usageFlags);
	}

	void DestroyBuffer(Buffer* targetBuffer) {
		pGI->DestroyBuffer(targetBuffer);
	}

	CommandBuffer* CreateCommandBuffer(const CommandBufferCreateInfo& create_info) {
		return pGI->CreateCommandBuffer(create_info);
	}

	void CmdSetViewport(CommandBuffer& commandBuffer) {
		pGI->CmdSetViewport(commandBuffer);
	}

	void CmdSetScissor(CommandBuffer& commandBuffer) {
		return;
	}

	void CmdSetLineWidth(CommandBuffer& commandBuffer) {
		return;
	}

	void CmdBindGraphicsPipeline(CommandBuffer& commandBuffer) {

	}

	void CmdBindIndexBuffer(CommandBuffer& commandBuffer) {

	}

	void CmdBindVertexBuffer(CommandBuffer& commandBuffer) {

	}

	void CmdDraw(CommandBuffer& commandBuffer) {

	}

	void CmdDrawIndexed(CommandBuffer& commandBuffer) {

	}
}
