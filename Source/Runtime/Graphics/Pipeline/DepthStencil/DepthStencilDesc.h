#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Pipeline/DepthStencil/DepthMask.h>
#include <Runtime/Graphics/Pipeline/DepthStencil/DepthStencilComparisonFunc.h>

struct DepthStencilDesc
{
	bool DepthEnable;
	DepthMask DepthMask;
	DepthStencilComparisonFunc DepthCompFunc;
	bool StencilEnable;
	byte StencilReadMask;
	byte StencilWriteMask;
};
