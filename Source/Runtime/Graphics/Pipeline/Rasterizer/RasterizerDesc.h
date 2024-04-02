#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Pipeline/Rasterizer/FillMode.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/CullMode.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/FaceOrdering.h>

struct RasterizerDesc
{
	FillMode FillMode;
	CullMode CullMode;
	FaceOrdering FaceOrdering;
	int DepthBias;
	float DepthClamp;
	float SlopeScaledDepthBias;
	bool DepthClipEnabled;
	bool ScissorEnabled;
	bool MultisampleEnabled;
	bool AntialiasedLineEnabled;
};
