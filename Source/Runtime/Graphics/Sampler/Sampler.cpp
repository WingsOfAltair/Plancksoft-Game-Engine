#include "Sampler.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>

#include <Runtime/Graphics/Sampler/SamplerUtils.h>

Sampler::Sampler(std::shared_ptr<GraphicsDevice> device, const SamplerDesc& desc)
{
	mOwnerDevice = device;

	mFilter = desc.Filter;
	mAddressU = desc.AddressU;
	mAddressV = desc.AddressV;
	mAddressW = desc.AddressW;
	mMipLODBias = desc.MipLODBias;
	mMaxAnisotropy = desc.MaxAnisotropy;
	mSamplerComparison = desc.SamplerComparison;
	this->mBorderColor[4] = desc.BorderColor[4];
	mMinLOD = desc.MinLOD;
	mMaxLOD	= desc.MaxLOD;

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = SamplerUtils::GetSamplerFilter(mFilter);
	samplerDesc.AddressU = SamplerUtils::GetSamplerAddressMode(mAddressU);
	samplerDesc.AddressV = SamplerUtils::GetSamplerAddressMode(mAddressV);
	samplerDesc.AddressW = SamplerUtils::GetSamplerAddressMode(mAddressW);
	samplerDesc.MipLODBias = mMipLODBias;
	samplerDesc.MaxAnisotropy = mMaxAnisotropy;
	samplerDesc.ComparisonFunc = SamplerUtils::GetSamplerComparisonFunc(mSamplerComparison);

	for (byte i = 0; i < 4; i++)
	{
		samplerDesc.BorderColor[i] = mBorderColor[i];
	}

	samplerDesc.MinLOD = mMinLOD;
	samplerDesc.MaxLOD = mMaxLOD;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateSamplerState(&samplerDesc, mSamplerState.GetAddressOf())), "Sampler", "Failed to create sampler state.");

}
