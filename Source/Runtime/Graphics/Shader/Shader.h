#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>

#include <Runtime/Graphics/Shader/ShaderDesc.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class Shader : public GraphicsDeviceObject
{
public:
	Shader(std::shared_ptr<GraphicsDevice> device, const ShaderDesc& desc);
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	virtual ~Shader() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Shader; }

	ComPtr<ID3D11VertexShader>& GetVertexShader() { return mVertexShader; }
	ComPtr<ID3D11HullShader>& GetHullShader() { return mHullShader; }
	ComPtr<ID3D11PixelShader>& GetPixelShader() { return mPixelShader; }
	ComPtr<ID3D11DomainShader>& GetDomainShader() { return mDomainShader; }
	ComPtr<ID3D11GeometryShader>& GetGeometryShader() { return mGeometryShader; }
	ComPtr<ID3D11ComputeShader>& GetComputeShader() { return mComputeShader; }

	ShaderType GetShaderType() const noexcept { return mShaderType; }
	const std::string& GetEntryPoint() const noexcept { return mEntryPoint; }
	const std::string& GetShaderName() const noexcept { return mShaderName; }

	ComPtr<ID3DBlob> GetShaderBlob() const noexcept { return mShaderBlob; }

private:
	ComPtr<ID3D11VertexShader> mVertexShader;
	ComPtr<ID3D11DomainShader> mDomainShader;
	ComPtr<ID3D11PixelShader> mPixelShader;
	ComPtr<ID3D11HullShader> mHullShader;
	ComPtr<ID3D11GeometryShader> mGeometryShader;
	ComPtr<ID3D11ComputeShader> mComputeShader;

	ComPtr<ID3DBlob> mShaderBlob;

	std::string mEntryPoint;
	std::string mShaderName;
	std::string mShaderModel;
	ShaderType mShaderType;
};
