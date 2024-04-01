#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>

#include <Runtime/Graphics/Pipeline/PipelineDesc.h>

class Pipeline : public GraphicsDeviceObject
{
public:
	Pipeline(std::shared_ptr<GraphicsDevice> device, const PipelineDesc& desc);
	~Pipeline() override = default;

	DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Pipeline; }

	std::vector<std::shared_ptr<Shader>>& GetShaders() noexcept { return mShaders; }
	InputLayoutDesc& GetInputLayout() noexcept { return mInputLayout; }
	RasterizerDesc& GetRasterizer() noexcept { return mRasterizer; }
	DepthStencilDesc& GetDepthStencil() noexcept { return mDepthStencil; }
	BlendStateDesc& GetBlend() noexcept { return mBlend; }
	std::shared_ptr<Sampler>& GetSampler() noexcept { return mSampler; }

	ComPtr<ID3D11InputLayout>& GetInputLayoutObject() { return mInputLayoutObject; }
	ComPtr<ID3D11RasterizerState>& GetRasterizerObject() { return mRasterizerObject; }
	ComPtr<ID3D11DepthStencilState>& GetDepthStencilObject() { return mDepthStencilObject; }
	ComPtr<ID3D11BlendState>& GetBlendObject() { return mBlendObject; }
	ComPtr<ID3D11SamplerState>& GetSamplerObject() { return mSamplerObject; }

	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology();

	void SetPrimitiveMode(PrimitiveMode mode) { mInputLayout.PrimitiveMode = mode; }

private:
	void CreateDepthStencilState();
	void CreateRasterizerState();
	void CreateBlendState();
private:
	std::vector<std::shared_ptr<Shader>> mShaders;
	InputLayoutDesc mInputLayout;
	RasterizerDesc mRasterizer;
	DepthStencilDesc mDepthStencil;
	BlendStateDesc mBlend;
	std::shared_ptr<Sampler> mSampler;

	ComPtr<ID3D11InputLayout> mInputLayoutObject;
	ComPtr<ID3D11RasterizerState> mRasterizerObject;
	ComPtr<ID3D11DepthStencilState> mDepthStencilObject;
	ComPtr<ID3D11BlendState> mBlendObject;
	ComPtr<ID3D11SamplerState> mSamplerObject;
};
