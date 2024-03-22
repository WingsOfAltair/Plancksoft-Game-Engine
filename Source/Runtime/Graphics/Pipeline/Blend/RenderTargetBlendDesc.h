#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Pipeline/Blend/BlendOperation.h>
#include <Runtime/Graphics/Pipeline/Blend/BlendType.h>
#include <Runtime/Graphics/Pipeline/Blend/ColorMask.h>

struct RenderTargetBlendDesc
{
	bool BlendEnable;
	BlendType SrcBlend;
	BlendType DestBlend;
	BlendOperation BlendOp;
	BlendType SrcBlendAlpha;
	BlendType DestBlendAlpha;
	BlendOperation BlendOpAlpha;
	ColorMask WriteMask;
};
