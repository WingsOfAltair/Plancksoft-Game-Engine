#include "Framebuffer.h"

#include <Runtime/Graphics/Texture/TextureUtils.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Texture/Texture.h>

Framebuffer::Framebuffer(std::shared_ptr<GraphicsDevice> device, const FramebufferDesc& desc)
{
	mOwnerDevice = device;
	mColorTexture = desc.pColorAttachment->GetTexture();

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = TextureUtils::GetTextureFormat(desc.ColorAttachmentFormat);
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateRenderTargetView(mColorTexture.Get(), &rtvDesc, mColorTextureView.GetAddressOf())), "Framebuffer",
		"Failed to create render target view for color texture.");

	D3D11_TEXTURE2D_DESC colorTextureDesc = {};
	mColorTexture->GetDesc(&colorTextureDesc);

	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = colorTextureDesc.Width;
	depthTextureDesc.Height = colorTextureDesc.Height;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.SampleDesc.Quality = 0;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateTexture2D(&depthTextureDesc, nullptr, mDepthTexture.GetAddressOf())), "Framebuffer",
		"Failed to create depth texture for Framebuffer.");

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = depthTextureDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateDepthStencilView(mDepthTexture.Get(), &dsvDesc, mDepthTextureView.GetAddressOf())), "Framebuffer",
		"Failed to create depth stencil view for depth texture.");

	DEV_LOG(TE_VERBOSE, "Framebuffer", "Created Framebuffer successfully.");
}