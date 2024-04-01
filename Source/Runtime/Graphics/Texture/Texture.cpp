#include "Texture.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Texture/TextureUtils.h>

Texture::Texture(std::shared_ptr<GraphicsDevice> device, const TextureDesc& desc) : mTextureSize(desc.TextureSize), mFormat(desc.Format),
mMipLevels(desc.MipLevels), mArraySize(desc.ArraySize), mSampleCount(desc.SampleCount), mSampleQuality(desc.SampleQuality)
{
	mOwnerDevice = device;

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = mTextureSize.x;
	textureDesc.Height = mTextureSize.y;
	textureDesc.MipLevels = mMipLevels;
	textureDesc.ArraySize = mArraySize;
	textureDesc.Format = TextureUtils::GetTextureFormat(mFormat);
	textureDesc.SampleDesc.Count = mSampleCount;
	textureDesc.SampleDesc.Quality = mSampleQuality;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = desc.InitialData;
	subresourceData.SysMemPitch = desc.TextureSize.x * TextureUtils::GetTextureFormatSize(mFormat);

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateTexture2D(&textureDesc, &subresourceData, mTexture.GetAddressOf())), "Texture",
				"Failed to create texture.");
}

Texture::Texture(std::shared_ptr<GraphicsDevice> device)
{
	mOwnerDevice = device;

	DEV_LOG(TE_INFO, "Texture", "Framebuffer Texture has been created.");
}
