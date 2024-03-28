#include "Object.h"

Object::Object(std::vector<VertexData> pArrayVertexData, std::vector<uint32_t> indexData)
{
	mIndexCount = indexData.size();

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
	vertexSubresourceData.pSysMem = pArrayVertexData.data();
	vertexSubresourceData.SysMemPitch = 0;
	vertexSubresourceData.SysMemSlicePitch = 0;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, mVertexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32_t) * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = indexData.data();
	indexSubresourceData.SysMemPitch = 0;
	indexSubresourceData.SysMemSlicePitch = 0;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexSubresourceData, mIndexBuffer.GetAddressOf());
}

void Object::SetProps()
{
	uint32_t stride = sizeof(VertexData);
	uint32_t offset = 0;

	RendererManager::GetRenderer()->GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	RendererManager::GetRenderer()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
