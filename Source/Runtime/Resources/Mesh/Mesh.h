#pragma once

#include <Runtime/Core/Core.h>

#include <DirectXMath.h>
using namespace DirectX;

#include <vector>
#include <memory>

class GraphicsBuffer;
class GraphicsDevice;
class CommandList;

class Mesh
{
public:
	Mesh() = default;
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	~Mesh() = default;

	void AllocateVertex();
	void AllocateIndex();

	std::shared_ptr<GraphicsBuffer> GetPositionBuffer() { return mPositionBuffer; }
	std::shared_ptr<GraphicsBuffer> GetNormalBuffer() { return mNormalBuffer; }
	std::shared_ptr<GraphicsBuffer> GetTangentBuffer() { return mTangentBuffer; }
	std::shared_ptr<GraphicsBuffer> GetBinormalBuffer() { return mBinormalBuffer; }
	std::shared_ptr<GraphicsBuffer> GetTexCoordBuffer() { return mTexCoordBuffer; }
	std::shared_ptr<GraphicsBuffer> GetIndexBuffer() { return mIndexBuffer; }

	std::vector<XMFLOAT3>& GetPositions() { return mPositions; }
	std::vector<XMFLOAT3>& GetNormals() { return mNormals; }
	std::vector<XMFLOAT3>& GetTangents() { return mTangents; }
	std::vector<XMFLOAT3>& GetBinormals() { return mBinormals; }
	std::vector<XMFLOAT2>& GetTexCoords() { return mTexCoords; }
	std::vector<uint16>& GetIndices() { return mIndices; }

private:
	std::vector<XMFLOAT3> mPositions;
	std::vector<XMFLOAT3> mNormals;
	std::vector<XMFLOAT3> mTangents;
	std::vector<XMFLOAT3> mBinormals;
	std::vector<XMFLOAT2> mTexCoords;
	std::vector<uint16> mIndices;

	std::shared_ptr<GraphicsBuffer> mPositionBuffer;
	std::shared_ptr<GraphicsBuffer> mNormalBuffer;
	std::shared_ptr<GraphicsBuffer> mTangentBuffer;
	std::shared_ptr<GraphicsBuffer> mBinormalBuffer;
	std::shared_ptr<GraphicsBuffer> mTexCoordBuffer;
	std::shared_ptr<GraphicsBuffer> mIndexBuffer;

	CommandList* mCommandList;
};
