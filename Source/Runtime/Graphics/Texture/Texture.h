#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Texture/TextureDesc.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class Texture : public GraphicsDeviceObject
{
	friend class Swapchain;
public:
	Texture(std::shared_ptr<GraphicsDevice> device, const TextureDesc& desc);
	Texture(std::shared_ptr<GraphicsDevice> device);
	virtual ~Texture() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Texture; }

	ComPtr<ID3D11Texture2D>& GetTexture() { return mTexture; }

	XMUINT3 GetTextureSize() const noexcept { return mTextureSize; }
	uint32 GetMipLevels() const noexcept { return mMipLevels; }
	uint32 GetArraySize() const noexcept { return mArraySize; }
	TextureFormat GetFormat() const noexcept { return mFormat; }
	uint32 GetSampleCount() const noexcept { return mSampleCount; }
	uint32 GetSampleQuality() const noexcept { return mSampleQuality; }

private:
	void SetFrameTexture(ComPtr<ID3D11Texture2D> texture) noexcept { mTexture = texture; }

private:
	XMUINT3 mTextureSize;
	uint32 mMipLevels;
	uint32 mArraySize;
	TextureFormat mFormat;
	uint32 mSampleCount;
	uint32 mSampleQuality;

	ComPtr<ID3D11Texture2D> mTexture;
};
