#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Texture/TextureViewDesc.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class TextureView : public GraphicsDeviceObject
{
public:
	TextureView(std::shared_ptr<GraphicsDevice> device, const TextureViewDesc& desc);
	TextureView(const TextureView&) = delete;
	TextureView& operator=(const TextureView&) = delete;
	virtual ~TextureView() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::TextureView; }

	ComPtr<ID3D11ShaderResourceView>& GetTextureView() { return mTextureView; }
	ComPtr<ID3D11Texture2D>& GetTexture() { return mTexture; }

	TextureFormat GetFormat() const noexcept { return mFormat; }
	ShaderResourceViewDimension GetSRVDimension() const noexcept { return mSRVDimension; }
	uint32 GetMostDetailedMip() const noexcept { return mMostDetailedMip; }
	uint32 GetMipLevels() const noexcept { return mMipLevels; }

private:
	TextureFormat mFormat;
	ShaderResourceViewDimension mSRVDimension;
	uint32 mMostDetailedMip;
	uint32 mMipLevels;

	ComPtr<ID3D11ShaderResourceView> mTextureView;
	ComPtr<ID3D11Texture2D> mTexture;
};
