#include "Application.h"

#include <Runtime/Graphics/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Command/CommandList.h>

void Application::Initialize()
{
	mWindow = WindowManager::GetInstance().GetWindow();
	mGraphicsDevice = GraphicsManager::GetInstance().GetMainDevice();

	SwapchainDesc swapchainDesc = {};
	swapchainDesc.Window = mWindow;
	swapchainDesc.SwapchainFormat = TextureFormat::RGBA8_UNSIGNED_NORMALIZED;
	swapchainDesc.BufferCount = 1;
	swapchainDesc.TargetFrameRate = 144;

	mSwapchain = mGraphicsDevice->CreateSwapchain(swapchainDesc);

	FramebufferDesc framebufferDesc = {};
	framebufferDesc.ColorAttachmentFormat = swapchainDesc.SwapchainFormat;
	framebufferDesc.pColorAttachment = mSwapchain->GetBackTexture();

	mFramebuffer = mGraphicsDevice->CreateFramebuffer(framebufferDesc);

	mCommandList = mGraphicsDevice->CreateCommandList();
}

void Application::Run()
{
	mWindow->ProcessMessage();
	mCommandList->BindFramebuffer(mFramebuffer);
	mCommandList->BindViewport(WindowManager::GetInstance().GetWindow()->GetWindowSize());
	mCommandList->ClearBuffer(mFramebuffer, { 0.2f, 0.3f, 0.5f });
}

bool Application::IsRunning()
{
	return mWindow->IsOpen();
}
