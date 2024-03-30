#include "Object.h"

#include <iostream>
#include <xutility>

#include <stb_image.h>

std::string GetProjectDir()
{
	std::string fullPath(__FILE__);
	size_t found = fullPath.find_last_of("/\\");
	if (found != std::string::npos)
	{
		std::string projectDir = fullPath.substr(0, found);

		found = projectDir.find_last_of("/\\");
		if (found != std::string::npos)
		{
			return projectDir.substr(0, found + 1);
		}
	}

	return "";
}

void Object::SetProps()
{
	uint32_t stride = sizeof(VertexData);
	uint32_t offset = 0;

	RendererManager::GetRenderer()->GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	RendererManager::GetRenderer()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	RendererManager::GetRenderer()->GetDeviceContext()->VSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());
	RendererManager::GetRenderer()->GetDeviceContext()->PSSetShaderResources(0, 1, mTextureView.GetAddressOf());
	RendererManager::GetRenderer()->GetDeviceContext()->PSSetSamplers(0, 1, mSamplerState.GetAddressOf());
}

void Object::UpdateMatrix(XMMATRIX view, XMMATRIX projection)
{			
	mWorldData.Rotation.z += 0.1f;

	mTransformData.World = XMMatrixTranspose(XMMatrixScaling(mWorldData.Scale.x, mWorldData.Scale.y, mWorldData.Scale.z) *
		XMMatrixRotationRollPitchYaw(XMConvertToRadians(mWorldData.Rotation.x), XMConvertToRadians(mWorldData.Rotation.y),
			XMConvertToRadians(mWorldData.Rotation.z)) * XMMatrixTranslation(mWorldData.Position.x, mWorldData.Position.y,
				mWorldData.Position.z));

	mTransformData.View = XMMatrixTranspose(view);
	mTransformData.Projection = XMMatrixTranspose(projection);

	D3D11_MAPPED_SUBRESOURCE mappedSubresource = {};
	RendererManager::GetRenderer()->GetDeviceContext()->Map(mConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	memcpy(mappedSubresource.pData, &mTransformData, sizeof(TransformData));
	RendererManager::GetRenderer()->GetDeviceContext()->Unmap(mConstantBuffer.Get(), 0);
}

void Object::InitBuffer()
{
	mWorldData =
	{
		.Position = { 0.0f, 0.0f, 0.0f },
		.Rotation = { 0.0f, 0.0f, 0.0f },
		.Scale = { 1.0f, 1.0f, 1.0f }
	};

	mTransformData = {
		.World = XMMatrixIdentity(),
		.View = XMMatrixIdentity(),
		.Projection = XMMatrixIdentity()
	};

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * mIndices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
	vertexSubresourceData.pSysMem = mVertices.data();
	vertexSubresourceData.SysMemPitch = 0;
	vertexSubresourceData.SysMemSlicePitch = 0;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, mVertexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32_t) * mIndices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = mIndices.data();
	indexSubresourceData.SysMemPitch = 0;
	indexSubresourceData.SysMemSlicePitch = 0;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexSubresourceData, mIndexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(TransformData);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA constantSubresourceData = {};
	constantSubresourceData.pSysMem = &mTransformData;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&constantBufferDesc, &constantSubresourceData, mConstantBuffer.GetAddressOf());

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 1.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	for (auto& el : samplerDesc.BorderColor)
	{
		el = 0.0f;
	}
	
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D10_FLOAT32_MAX;

	RendererManager::GetRenderer()->GetDevice()->CreateSamplerState(&samplerDesc, mSamplerState.GetAddressOf());
	
	std::string path = GetProjectDir() + "Textures\\";

	// Load image data
	mTextureData = stbi_load((path + "Brick_Color.png").c_str(), &mTextureSize.x, &mTextureSize.y, &mTextureSize.z, 4);
	if (!mTextureData) {
		printf("Failed to load image data.\n");
		// Handle error appropriately
	}

	// Texture description
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = mTextureSize.x;
	textureDesc.Height = mTextureSize.y;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Adjust format if necessary
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	// Texture subresource data
	D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
	textureSubresourceData.pSysMem = mTextureData;
	textureSubresourceData.SysMemPitch = mTextureSize.x * 4 * sizeof(uint8_t);

	// Create texture
	if (FAILED(RendererManager::GetRenderer()->GetDevice()->CreateTexture2D(&textureDesc, &textureSubresourceData, mTexture.GetAddressOf()))) {
		printf("Failed to create 2D texture.\n");
		// Handle error appropriately
	}

	// Shader resource view description
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = textureDesc.MipLevels;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

	// Create shader resource view
	if (FAILED(RendererManager::GetRenderer()->GetDevice()->CreateShaderResourceView(mTexture.Get(), &shaderResourceViewDesc, mTextureView.GetAddressOf()))) {
		printf("Failed to create shader resource view.\n");
		// Handle error appropriately
	}

}
