#include "TextureResource.h"

#include <Runtime/Graphics/GraphicsManager.h>

void TextureResource::AllocateTexture()
{
	TextureDesc textureDesc;
	textureDesc.TextureSize = XMUINT3(mWidth, mHeight, 1);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = TextureFormat::RGBA8_UNSIGNED_NORMALIZED;
	textureDesc.SampleCount = 1;
	textureDesc.SampleQuality = 0;
	textureDesc.InitialData = mPixelData;

	mTexture = GraphicsManager::GetInstance().GetMainDevice()->CreateTexture(textureDesc);

	TextureViewDesc textureViewDesc;
	textureViewDesc.Format = textureDesc.Format;
	textureViewDesc.SRVDimension = ShaderResourceViewDimension::TEXTURE2D;
	textureViewDesc.MostDetailedMip = 0;
	textureViewDesc.MipLevels = textureDesc.MipLevels;

	textureViewDesc.pTexture = mTexture.get();

	mTextureView = GraphicsManager::GetInstance().GetMainDevice()->CreateTextureView(textureViewDesc);
}
