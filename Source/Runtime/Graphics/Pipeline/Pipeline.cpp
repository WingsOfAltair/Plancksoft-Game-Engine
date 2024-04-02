#include "Pipeline.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Pipeline/PipelineUtils.h>
#include <Runtime/Graphics/Sampler/SamplerUtils.h>
#include <Runtime/Graphics/Texture/TextureUtils.h>

Pipeline::Pipeline(std::shared_ptr<GraphicsDevice> device, const PipelineDesc& desc)
{
	mOwnerDevice = device;
	mShaders = desc.Shaders;
	mInputLayout = desc.InputLayout;
	mRasterizer = desc.Rasterizer;
	mDepthStencil = desc.DepthStencil;
	mBlend = desc.Blend;
	mSampler = desc.Sampler;

	mSamplerObject = mSampler->GetSamplerState();

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescs;

	for (uint32 i = 0; i < mInputLayout.SemanticNames.size(); i++)
	{
		D3D11_INPUT_ELEMENT_DESC inputElementDesc;

		switch (mInputLayout.SemanticNames[i])
		{
			case SemanticName::Position:
			{
				inputElementDesc.SemanticName = "POSITION";
				inputElementDesc.Format = TextureUtils::GetTextureFormat(mInputLayout.InputFormats[i]);
				break;
			}
			case SemanticName::Normal:
			{
				inputElementDesc.SemanticName = "NORMAL";
				inputElementDesc.Format = TextureUtils::GetTextureFormat(mInputLayout.InputFormats[i]);
				break;
			}
			case SemanticName::Tangent:
			{
				inputElementDesc.SemanticName = "TANGENT";
				inputElementDesc.Format = TextureUtils::GetTextureFormat(mInputLayout.InputFormats[i]);
				break;
			}
			case SemanticName::BiNormal:
			{
				inputElementDesc.SemanticName = "BINORMAL";
				inputElementDesc.Format = TextureUtils::GetTextureFormat(mInputLayout.InputFormats[i]);
				break;
			}
			case SemanticName::TexCoord:
			{
				inputElementDesc.SemanticName = "TEXCOORD";
				inputElementDesc.Format = TextureUtils::GetTextureFormat(mInputLayout.InputFormats[i]);
				break;
			}
			case SemanticName::Color:
			{
				inputElementDesc.SemanticName = "COLOR";
				inputElementDesc.Format = TextureUtils::GetTextureFormat(mInputLayout.InputFormats[i]);
				break;
			}
		}

		inputElementDesc.SemanticIndex = mInputLayout.SemanticIndices[i];
		inputElementDesc.InputSlot = mInputLayout.InputSlotIndices[i];
		inputElementDesc.AlignedByteOffset = mInputLayout.AlignedByteOffsets[i];
		inputElementDesc.InputSlotClass = PipelineUtils::GetInputClassification(mInputLayout.SlotClasses[i]);
		inputElementDesc.InstanceDataStepRate = mInputLayout.InstanceDataSteps[i];

		inputElementDescs.push_back(inputElementDesc);
	}

	for (auto& shader : mShaders)
	{
		if (shader->GetShaderType() == ShaderType::VERTEX_SHADER)
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateInputLayout(inputElementDescs.data(), (uint32)inputElementDescs.size(), shader->GetShaderBlob()->GetBufferPointer(), shader->GetShaderBlob()->GetBufferSize(), mInputLayoutObject.GetAddressOf())), "Pipeline",
								"Failed to create input layout.");
		}
	}

	CreateDepthStencilState();
	CreateRasterizerState();
	CreateBlendState();
}

D3D11_PRIMITIVE_TOPOLOGY Pipeline::GetPrimitiveTopology()
{
	return PipelineUtils::GetPrimitiveTopology(mInputLayout.PrimitiveMode);
}

void Pipeline::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = mDepthStencil.DepthEnable;
	depthStencilDesc.DepthWriteMask = PipelineUtils::GetDepthWriteMask(mDepthStencil.DepthMask);
	depthStencilDesc.DepthFunc = PipelineUtils::GetDepthComparisonFunc(mDepthStencil.DepthCompFunc);
	depthStencilDesc.StencilEnable = mDepthStencil.StencilEnable;
	depthStencilDesc.StencilReadMask = mDepthStencil.StencilReadMask;
	depthStencilDesc.StencilWriteMask = mDepthStencil.StencilWriteMask;

	DEV_ASSERT(SUCCEEDED(mOwnerDevice->GetD3D11Device()->CreateDepthStencilState(&depthStencilDesc, mDepthStencilObject.GetAddressOf())), "Pipeline",
								"Failed to create depth stencil state.");
}

void Pipeline::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = PipelineUtils::GetFillMode(mRasterizer.FillMode);
	rasterizerDesc.CullMode = PipelineUtils::GetCullMode(mRasterizer.CullMode);
	rasterizerDesc.FrontCounterClockwise = PipelineUtils::GetFaceOrdering(mRasterizer.FaceOrdering);
	rasterizerDesc.DepthBias = mRasterizer.DepthBias;
	rasterizerDesc.DepthBiasClamp = mRasterizer.DepthClamp;
	rasterizerDesc.SlopeScaledDepthBias = mRasterizer.SlopeScaledDepthBias;
	rasterizerDesc.DepthClipEnable = mRasterizer.DepthClipEnabled;
	rasterizerDesc.ScissorEnable = mRasterizer.ScissorEnabled;
	rasterizerDesc.MultisampleEnable = mRasterizer.MultisampleEnabled;
	rasterizerDesc.AntialiasedLineEnable = mRasterizer.AntialiasedLineEnabled;

	DEV_ASSERT(SUCCEEDED(mOwnerDevice->GetD3D11Device()->CreateRasterizerState(&rasterizerDesc, mRasterizerObject.GetAddressOf())), "Pipeline",
										"Failed to create rasterizer state.");
}

void Pipeline::CreateBlendState()
{
	D3D11_RENDER_TARGET_BLEND_DESC rtvBlendDesc = {};
	rtvBlendDesc.BlendEnable = mBlend.RenderTargetBlendDescs.BlendEnable;
	rtvBlendDesc.SrcBlend = PipelineUtils::GetBlendType(mBlend.RenderTargetBlendDescs.SrcBlend);
	rtvBlendDesc.DestBlend = PipelineUtils::GetBlendType(mBlend.RenderTargetBlendDescs.DestBlend);
	rtvBlendDesc.BlendOp = PipelineUtils::GetBlendOp(mBlend.RenderTargetBlendDescs.BlendOp);
	rtvBlendDesc.SrcBlendAlpha = PipelineUtils::GetBlendType(mBlend.RenderTargetBlendDescs.SrcBlendAlpha);
	rtvBlendDesc.DestBlendAlpha = PipelineUtils::GetBlendType(mBlend.RenderTargetBlendDescs.DestBlendAlpha);
	rtvBlendDesc.BlendOpAlpha = PipelineUtils::GetBlendOp(mBlend.RenderTargetBlendDescs.BlendOpAlpha);
	rtvBlendDesc.RenderTargetWriteMask = PipelineUtils::GetColorWriteMask(mBlend.RenderTargetBlendDescs.WriteMask);

	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = mBlend.AlphaToCoverageEnable;
	blendDesc.IndependentBlendEnable = mBlend.IndependentBlendEnable;
	blendDesc.RenderTarget[0] = rtvBlendDesc;

	DEV_ASSERT(SUCCEEDED(mOwnerDevice->GetD3D11Device()->CreateBlendState(&blendDesc, mBlendObject.GetAddressOf())), "Pipeline",
																										"Failed to create blend state.");

}
