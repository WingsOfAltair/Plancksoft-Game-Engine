#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Sampler/SamplerFilter.h>
#include <Runtime/Graphics/Sampler/AddressMode.h>
#include <Runtime/Graphics/Sampler/SamplerComparison.h>

#include <d3d11.h>

class SamplerUtils
{
public:
	static D3D11_FILTER GetSamplerFilter(SamplerFilter filter)
	{
        switch (filter) {
        case SamplerFilter::MIN_MAG_MIP_POINT:
            return D3D11_FILTER_MIN_MAG_MIP_POINT;
        case SamplerFilter::MIN_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::MIN_POINT_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::MIN_POINT_MAG_MIP_LINEAR:
            return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
        case SamplerFilter::MIN_LINEAR_MAG_MIP_POINT:
            return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
        case SamplerFilter::MIN_LINEAR_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::MIN_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::MIN_MAG_MIP_LINEAR:
            return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        case SamplerFilter::ANISOTROPIC:
            return D3D11_FILTER_ANISOTROPIC;
        case SamplerFilter::COMPARISON_MIN_MAG_MIP_POINT:
            return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
        case SamplerFilter::COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
            return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
        case SamplerFilter::COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
            return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
        case SamplerFilter::COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::COMPARISON_MIN_MAG_MIP_LINEAR:
            return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
        case SamplerFilter::COMPARISON_ANISOTROPIC:
            return D3D11_FILTER_COMPARISON_ANISOTROPIC;
        case SamplerFilter::MINIMUM_MIN_MAG_MIP_POINT:
            return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
        case SamplerFilter::MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
            return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
        case SamplerFilter::MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
            return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
        case SamplerFilter::MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::MINIMUM_MIN_MAG_MIP_LINEAR:
            return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
        case SamplerFilter::MINIMUM_ANISOTROPIC:
            return D3D11_FILTER_MINIMUM_ANISOTROPIC;
        case SamplerFilter::MAXIMUM_MIN_MAG_MIP_POINT:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
        case SamplerFilter::MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
            return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
        case SamplerFilter::MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
            return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
        case SamplerFilter::MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
            return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case SamplerFilter::MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
        case SamplerFilter::MAXIMUM_MIN_MAG_MIP_LINEAR:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
        case SamplerFilter::MAXIMUM_ANISOTROPIC:
            return D3D11_FILTER_MAXIMUM_ANISOTROPIC;
        default:
            return D3D11_FILTER_MIN_MAG_MIP_POINT;
        }
	}
    static D3D11_TEXTURE_ADDRESS_MODE GetSamplerAddressMode(AddressMode addressMode)
    {
        switch (addressMode) {
		case AddressMode::WRAP:
			return D3D11_TEXTURE_ADDRESS_WRAP;
		case AddressMode::MIRROR:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case AddressMode::CLAMP:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		case AddressMode::BORDER:
			return D3D11_TEXTURE_ADDRESS_BORDER;
		case AddressMode::MIRROR_ONCE:
			return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
		default:
			return D3D11_TEXTURE_ADDRESS_WRAP;
		}
    }
    static D3D11_COMPARISON_FUNC GetSamplerComparisonFunc(SamplerComparison comparisonFunc)
    {
        switch (comparisonFunc)
        {
        case SamplerComparison::NEVER:
            return D3D11_COMPARISON_NEVER;
        case SamplerComparison::LESS:
            return D3D11_COMPARISON_LESS;
        case SamplerComparison::EQUAL:
            return D3D11_COMPARISON_EQUAL;
        case SamplerComparison::LESS_EQUAL:
            return D3D11_COMPARISON_LESS_EQUAL;
        case SamplerComparison::GREATER:
            return D3D11_COMPARISON_GREATER;
        case SamplerComparison::NOT_EQUAL:
            return D3D11_COMPARISON_NOT_EQUAL;
        case SamplerComparison::GREATER_EQUAL:
            return D3D11_COMPARISON_GREATER_EQUAL;
        case SamplerComparison::ALWAYS:
            return D3D11_COMPARISON_ALWAYS;
        default:
            return D3D11_COMPARISON_NEVER;
        }
    }
public:
	SamplerUtils() = delete;
	~SamplerUtils() = delete;
};
