#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/Graphics/Texture/TextureView.h>

#include <memory>

class TextureResource
{
public:
	TextureResource() = default;
	TextureResource(const TextureResource&) = delete;
	TextureResource& operator=(const TextureResource&) = delete;
	~TextureResource() = default;

	void AllocateTexture();

	std::shared_ptr<Texture>& GetTexture() { return mTexture; }
	std::shared_ptr<TextureView>& GetTextureView() { return mTextureView; }

	uint32& GetWidth() noexcept { return mWidth; }
	uint32& GetHeight() noexcept { return mHeight; }
	uint32& GetChannels() noexcept { return mChannels; }
	uint8** GetPixelData() noexcept { return &mPixelData; }

public:
	void SetTexture(byte* data, uint32 width, uint32 height, uint32 channels)
	{
		mPixelData = data; mWidth = width; mHeight = height; mChannels = channels;
	}
private:
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<TextureView> mTextureView;

	uint32 mWidth;
	uint32 mHeight;
	uint32 mChannels;

	uint8* mPixelData;
};
