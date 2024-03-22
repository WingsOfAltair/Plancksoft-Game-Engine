#pragma once

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>

#include <Runtime/Graphics/Swapchain/SwapchainDesc.h>

#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Texture;

class Swapchain : public GraphicsDeviceObject
{
public:
	Swapchain(std::shared_ptr<GraphicsDevice> device, const SwapchainDesc& desc);
	virtual ~Swapchain() override;

	void Present();

	Texture* GetBackTexture() { return mBackTexture; }
	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Swapchain; }

private:
	Texture* mBackTexture;
	ComPtr<IDXGISwapChain> mSwapchain;

	ComPtr<IDXGIDevice> mDXGIDevice;
	ComPtr<IDXGIAdapter> mDXGIAdapter;
	ComPtr<IDXGIFactory> mDXGIFactory;
};
