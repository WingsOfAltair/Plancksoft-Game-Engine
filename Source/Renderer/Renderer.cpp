#include<stdio.h>
#include "Renderer.h"

Renderer::Renderer(Window* pWindow) : mWindow(pWindow), mDevice(nullptr), mDeviceContext(nullptr),
mSwapChain(nullptr), mRenderTargetView(nullptr)
{
	CreateDevice();
	CreateSwapChain();
	CreateRenderTargetView();
}

void Renderer::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 1,
		D3D11_SDK_VERSION, mDevice.GetAddressOf(), nullptr, mDeviceContext.GetAddressOf())))
	{
		printf("Failed to create d3d11 device and context.\n");
		abort();
	}
	else
	{
		printf("Successfully created d3d11 device.\n");
	}

}

void Renderer::CreateSwapChain()
{

}

void Renderer::CreateRenderTargetView()
{
}

void Renderer::ClearColor(XMFLOAT3 color)
{
}

void Renderer::Present()
{
}
