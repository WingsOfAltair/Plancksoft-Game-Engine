#include "ObjectPipeline.h"

#include <Runtime/Graphics/GraphicsManager.h>

#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Sampler/Sampler.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>

ObjectPipeline::ObjectPipeline()
{
	ShaderDesc vertexShaderDesc = {};
	vertexShaderDesc.Type = ShaderType::VERTEX_SHADER;
	vertexShaderDesc.EntryPoint = "vs_main";
	vertexShaderDesc.ShaderName = "ObjectVertexShader";
	vertexShaderDesc.ShaderModel = "vs_5_0";

	mVertexShader = GraphicsManager::GetInstance().GetMainDevice()->CreateShader(vertexShaderDesc);

	ShaderDesc pixelShaderDesc = {};
	pixelShaderDesc.Type = ShaderType::PIXEL_SHADER;
	pixelShaderDesc.EntryPoint = "ps_main";
	pixelShaderDesc.ShaderName = "ObjectPixelShader";
	pixelShaderDesc.ShaderModel = "ps_5_0";

	mPixelShader = GraphicsManager::GetInstance().GetMainDevice()->CreateShader(pixelShaderDesc);

	SamplerDesc samplerDesc = {};
	samplerDesc.Filter = SamplerFilter::MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = AddressMode::WRAP;
	samplerDesc.AddressV = AddressMode::WRAP;
	samplerDesc.AddressW = AddressMode::WRAP;
	samplerDesc.SamplerComparison = SamplerComparison::ALWAYS;
	samplerDesc.MipLODBias = 1.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = FloatMax;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;

	mSampler = GraphicsManager::GetInstance().GetMainDevice()->CreateSampler(samplerDesc);

	InputLayoutDesc inputDesc = {};
	inputDesc.SemanticNames = { SemanticName::Position, SemanticName::TexCoord, SemanticName::Normal };
	inputDesc.InputFormats = { TextureFormat::RGB32_FLOAT, TextureFormat::RGB32_FLOAT, TextureFormat::RGB32_FLOAT };
	inputDesc.SemanticIndices = { 0, 0, 0 };
	inputDesc.InputSlotIndices = { 0, 1, 2 };
	inputDesc.AlignedByteOffsets = { D3D11_APPEND_ALIGNED_ELEMENT, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_APPEND_ALIGNED_ELEMENT };
	inputDesc.SlotClasses = { SlotClass::PerVertexData, SlotClass::PerVertexData, SlotClass::PerVertexData };
	inputDesc.InstanceDataSteps = { 0, 0, 0 };
	inputDesc.PrimitiveMode = PrimitiveMode::TriangleList;

	RasterizerDesc rasterizerDesc = {};
	rasterizerDesc.FillMode = FillMode::Solid;
	rasterizerDesc.CullMode = CullMode::Back;
	rasterizerDesc.FaceOrdering = FaceOrdering::Clockwise;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthClamp = 0.0f;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.DepthClipEnabled = false;
	rasterizerDesc.ScissorEnabled = false;
	rasterizerDesc.MultisampleEnabled = true;
	rasterizerDesc.AntialiasedLineEnabled = true;

	DepthStencilDesc depthDesc = {};
	depthDesc.DepthEnable = true;
	depthDesc.DepthMask = DepthMask::All;
	depthDesc.DepthCompFunc = DepthStencilComparisonFunc::Less;
	depthDesc.StencilEnable = false;
	depthDesc.StencilReadMask = 0xFF;
	depthDesc.StencilWriteMask = 0xFF;

	BlendStateDesc blendDesc = {};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = true;
	blendDesc.RenderTargetBlendDescs = {
					.BlendEnable = true,
					.SrcBlend = BlendType::One,
					.DestBlend = BlendType::Zero,
					.BlendOp = BlendOperation::Add,
					.SrcBlendAlpha = BlendType::One,
					.DestBlendAlpha = BlendType::Zero,
					.BlendOpAlpha = BlendOperation::Add,
					.WriteMask = ColorMask::All
	};

	PipelineDesc pipelineDesc = {};
	pipelineDesc.Shaders = { mVertexShader, mPixelShader };
	pipelineDesc.InputLayout = inputDesc;
	pipelineDesc.Rasterizer = rasterizerDesc;
	pipelineDesc.DepthStencil = depthDesc;
	pipelineDesc.Blend = blendDesc;
	pipelineDesc.Sampler = mSampler;

	mPipeline = GraphicsManager::GetInstance().GetMainDevice()->CreatePipeline(pipelineDesc);
}
