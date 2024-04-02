#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Framebuffer/FramebufferDesc.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class Framebuffer : public GraphicsDeviceObject
{
public:
	Framebuffer(std::shared_ptr<GraphicsDevice> device, const FramebufferDesc& desc);
	Framebuffer(const Framebuffer&) = delete;
	Framebuffer& operator=(const Framebuffer&) = delete;
	virtual ~Framebuffer() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Framebuffer; }

	ComPtr<ID3D11Texture2D>& GetColorTexture() { return mColorTexture; }
	ComPtr<ID3D11Texture2D>& GetDepthTexture() { return mDepthTexture; }

	ComPtr<ID3D11RenderTargetView>& GetColorTextureView() { return mColorTextureView; }
	ComPtr<ID3D11DepthStencilView>& GetDepthTextureView() { return mDepthTextureView; }

private:
	ComPtr<ID3D11Texture2D> mColorTexture;
	ComPtr<ID3D11RenderTargetView> mColorTextureView;
	ComPtr<ID3D11Texture2D> mDepthTexture;
	ComPtr<ID3D11DepthStencilView> mDepthTextureView;
};
