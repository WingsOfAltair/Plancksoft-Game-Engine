#include "TextureView.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Texture/TextureUtils.h>

#include <Runtime/Graphics/Texture/Texture.h>

TextureView::TextureView(std::shared_ptr<GraphicsDevice> device, const TextureViewDesc& desc) : mTexture(desc.pTexture->GetTexture()),
mFormat(desc.Format), mSRVDimension(desc.SRVDimension), mMostDetailedMip(desc.MostDetailedMip), mMipLevels(desc.MipLevels)
{
	mOwnerDevice = device;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = TextureUtils::GetTextureFormat(mFormat);
	srvDesc.ViewDimension = TextureUtils::GetSRVDimension(mSRVDimension);
	srvDesc.Texture2D.MostDetailedMip = mMostDetailedMip;
	srvDesc.Texture2D.MipLevels = mMipLevels;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateShaderResourceView(mTexture.Get(), &srvDesc, mTextureView.GetAddressOf())), "TextureView",
				"Failed to create shader resource view for texture.");

}
