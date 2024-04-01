#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>

#include <Runtime/Graphics/Sampler/SamplerDesc.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class Sampler : public GraphicsDeviceObject
{
public:
	Sampler(std::shared_ptr<GraphicsDevice> device, const SamplerDesc& desc);
	~Sampler() override = default;

	DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Sampler; }

	const SamplerFilter& GetFilter() const noexcept { return mFilter; }
	AddressMode GetAddressU() const noexcept { return mAddressU; }
	AddressMode GetAddressV() const noexcept { return mAddressV; }
	AddressMode GetAddressW() const noexcept { return mAddressW; }
	float GetMipLODBias() const noexcept { return mMipLODBias; }
	uint32 GetMaxAnisotropy() const noexcept { return mMaxAnisotropy; }
	SamplerComparison GetSamplerComparison() const noexcept { return mSamplerComparison; }
	const float* GetBorderColor() const noexcept { return mBorderColor; }
	float GetMinLOD() const noexcept { return mMinLOD; }
	float GetMaxLOD() const noexcept { return mMaxLOD; }

	ComPtr<ID3D11SamplerState>& GetSamplerState() { return mSamplerState; }
private:
	SamplerFilter mFilter;
	AddressMode mAddressU;
	AddressMode mAddressV;
	AddressMode mAddressW;
	float mMipLODBias;
	uint32 mMaxAnisotropy;
	SamplerComparison mSamplerComparison;
	float mBorderColor[4];
	float mMinLOD;
	float mMaxLOD;

	ComPtr<ID3D11SamplerState> mSamplerState;
};
