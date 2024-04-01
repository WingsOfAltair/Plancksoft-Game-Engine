#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Sampler/SamplerFilter.h>
#include <Runtime/Graphics/Sampler/AddressMode.h>
#include <Runtime/Graphics/Sampler/SamplerComparison.h>

struct SamplerDesc
{
	SamplerFilter Filter;
	AddressMode AddressU;
	AddressMode AddressV;
	AddressMode AddressW;
	float MipLODBias;
	uint32 MaxAnisotropy;
	SamplerComparison SamplerComparison;
	float BorderColor[4];
	float MinLOD;
	float MaxLOD;
};
