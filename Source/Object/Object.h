#pragma once

#include <Renderer/RendererManager.h>

#include<vector>

struct VertexData
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

class Object
{
public:
	Object(std::vector<VertexData> pArrayVertexData, std::vector<uint32_t> indexData);
	~Object() = default;

	void SetProps();

	uint32_t GetIndexCount() const { return mIndexCount; }

private:
	ComPtr<ID3D11Buffer> mVertexBuffer;
	ComPtr<ID3D11Buffer> mIndexBuffer;
	uint32_t mIndexCount;
};