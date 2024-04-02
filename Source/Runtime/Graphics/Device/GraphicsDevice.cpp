#include "GraphicsDevice.h"

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Framebuffer/FramebufferDesc.h>

#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Swapchain/SwapchainDesc.h>

#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/Graphics/Texture/TextureDesc.h>

#include <Runtime/Graphics/Texture/TextureView.h>
#include <Runtime/Graphics/Texture/TextureViewDesc.h>

#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Shader/ShaderDesc.h>

#include <Runtime/Graphics/Pipeline/Pipeline.h>

#include <Runtime/Graphics/Sampler/Sampler.h>

#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>

#include <Runtime/Graphics/Command/CommandList.h>

GraphicsDevice::GraphicsDevice()
{
	DEV_ASSERT(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&mD3D11Device, nullptr, &mD3D11ImmediateContext)), "GraphicsDevice",
		"Failed to create D3D11 device.");

	DEV_LOG(TE_VERBOSE, "GraphicsDevice", "Created GraphicsDevice successfully.");
}

std::shared_ptr<Swapchain> GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
{
	mSwapchain = std::make_shared<Swapchain>(shared_from_this(), desc);
	mDeviceObjects.push_back(mSwapchain);

	return mSwapchain;
}

std::shared_ptr<Framebuffer> GraphicsDevice::CreateFramebuffer(const FramebufferDesc& desc)
{
	auto framebuffer = std::make_shared<Framebuffer>(shared_from_this(), desc);
	mDeviceObjects.push_back(framebuffer);

	return framebuffer;
}

std::shared_ptr<Texture> GraphicsDevice::CreateTexture(const TextureDesc& desc)
{
	auto texture = std::make_shared<Texture>(shared_from_this(), desc);
	mDeviceObjects.push_back(texture);

	return texture;
}

std::shared_ptr<TextureView> GraphicsDevice::CreateTextureView(const TextureViewDesc& desc)
{
	auto textureView = std::make_shared<TextureView>(shared_from_this(), desc);
	mDeviceObjects.push_back(textureView);

	return textureView;
}

std::shared_ptr<Shader> GraphicsDevice::CreateShader(const ShaderDesc& desc)
{
	auto shader = std::make_shared<Shader>(shared_from_this(), desc);
	mDeviceObjects.push_back(shader);

	return shader;
}

std::shared_ptr<Pipeline> GraphicsDevice::CreatePipeline(const PipelineDesc& desc)
{
	auto pipeline = std::make_shared<Pipeline>(shared_from_this(), desc);
	mDeviceObjects.push_back(pipeline);

	return pipeline;
}

std::shared_ptr<Sampler> GraphicsDevice::CreateSampler(const SamplerDesc& desc)
{
	auto sampler = std::make_shared<Sampler>(shared_from_this(), desc);
	mDeviceObjects.push_back(sampler);

	return sampler;
}

std::shared_ptr<CommandList> GraphicsDevice::CreateCommandList()
{
	auto commandList = std::make_shared<CommandList>(shared_from_this());
	mDeviceObjects.push_back(commandList);

	return commandList;
}

std::shared_ptr<GraphicsBuffer> GraphicsDevice::CreateGraphicsBuffer(const GraphicsBufferDesc& desc)
{
	auto graphicsBuffer = std::make_shared<GraphicsBuffer>(shared_from_this(), desc);
	mDeviceObjects.push_back(graphicsBuffer);

	return graphicsBuffer;
}

void GraphicsDevice::ExecuteCommandLists(std::vector<std::shared_ptr<CommandList>> commandLists)
{
	for (auto& commandList : commandLists)
	{
		commandList->GetDeferredContext()->FinishCommandList(false, commandList->GetCommandList().GetAddressOf());
		mD3D11ImmediateContext->ExecuteCommandList(commandList->GetCommandList().Get(), false);
		commandList->ClearCommandList();
	}
}

void GraphicsDevice::Present()
{
	mSwapchain->Present();
}
