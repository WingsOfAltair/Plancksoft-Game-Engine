#include "Shader.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>

#include <Runtime/Graphics/Shader/ShaderReader.h>

Shader::Shader(std::shared_ptr<GraphicsDevice> device, const ShaderDesc& desc)
{
	mOwnerDevice = device;
	mEntryPoint = desc.EntryPoint;
	mShaderName = desc.ShaderName;
	mShaderType = desc.Type;
	mShaderModel = desc.ShaderModel;

	ComPtr<ID3DBlob> errorBlob;

	std::string shaderBlob = ShaderReader::ReadShaderFile(mShaderName);

	D3DCompile(shaderBlob.data(), shaderBlob.length(), nullptr, nullptr, nullptr, mEntryPoint.c_str(),
		mShaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, mShaderBlob.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob.Get() != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		DEV_LOG(TE_FATAL, "Shader", "Failed to compile shader: %s", (char*)errorBlob->GetBufferPointer());
	}

	switch (mShaderType)
	{
		case ShaderType::VERTEX_SHADER:
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateVertexShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mVertexShader.GetAddressOf())), "Shader",
								"Failed to create vertex shader.");
			break;
		}
		case ShaderType::PIXEL_SHADER:
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreatePixelShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mPixelShader.GetAddressOf())), "Shader",
												"Failed to create pixel shader.");
			break;
		}
		case ShaderType::GEOMETRY_SHADER:
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateGeometryShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mGeometryShader.GetAddressOf())), "Shader",
																"Failed to create geometry shader.");
			break;
		}
		case ShaderType::HULL_SHADER:
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateHullShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mHullShader.GetAddressOf())), "Shader",
																										"Failed to create hull shader.");
			break;
		}
		case ShaderType::DOMAIN_SHADER:
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateDomainShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mDomainShader.GetAddressOf())), "Shader",
																																"Failed to create domain shader.");
			break;
		}
		case ShaderType::COMPUTE_SHADER:
		{
			DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateComputeShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mComputeShader.GetAddressOf())), "Shader",
																																					"Failed to create compute shader.");
			break;
		}
		default:
		{
			DEV_ASSERT(false, "Shader", "Unknown shader type.");
			break;
		}
	}

	
	DEV_LOG(TE_VERBOSE, "Shader", "%s has been created successfully.", mShaderName.c_str());
}
