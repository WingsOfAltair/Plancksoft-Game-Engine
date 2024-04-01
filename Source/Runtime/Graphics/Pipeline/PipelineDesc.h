#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Shader/Shader.h>

#include <Runtime/Graphics/Pipeline/InputLayout/InputLayoutDesc.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/RasterizerDesc.h>
#include <Runtime/Graphics/Pipeline/DepthStencil/DepthStencilDesc.h>
#include <Runtime/Graphics/Pipeline/Blend/BlendStateDesc.h>
#include <Runtime/Graphics/Sampler/Sampler.h>

#include <memory>
#include <vector>

struct PipelineDesc
{
	std::vector<std::shared_ptr<Shader>> Shaders;
	InputLayoutDesc InputLayout;
	RasterizerDesc Rasterizer;
	DepthStencilDesc DepthStencil;
	BlendStateDesc Blend;
	std::shared_ptr<Sampler> Sampler;
};
