#pragma warning(disable: 4267)

#include "Mesh.h"

#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Command/CommandList.h>

#include <Runtime/Graphics/GraphicsManager.h>

void Mesh::AllocateVertex()
{
	GraphicsBufferDesc desc;
	desc.ResourceUsage = ResourceUsage::DEFAULT;
	desc.Usage = BufferUsage::VERTEX_BUFFER;
	desc.CPUAccess = BufferCPUAccess::NONE;
	desc.SizeInBytes = sizeof(XMFLOAT3) * mPositions.size();
	desc.StructureByteStride = sizeof(XMFLOAT3);
	desc.MiscFlags = 0;
	desc.InitialData = mPositions.data();

	if(mPositions.size() != 0)
		mPositionBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);

	desc.SizeInBytes = sizeof(XMFLOAT3) * mNormals.size();
	desc.StructureByteStride = sizeof(XMFLOAT3);
	desc.InitialData = mNormals.data();

	if(mNormals.size() != 0)
		mNormalBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);

	desc.SizeInBytes = sizeof(XMFLOAT3) * mTangents.size();
	desc.StructureByteStride = sizeof(XMFLOAT3);
	desc.InitialData = mTangents.data();

	if(mTangents.size() != 0)
		mTangentBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);

	desc.SizeInBytes = sizeof(XMFLOAT3) * mBinormals.size();
	desc.StructureByteStride = sizeof(XMFLOAT3);
	desc.InitialData = mBinormals.data();

	if(mBinormals.size() != 0)
		mBinormalBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);

	desc.SizeInBytes = sizeof(XMFLOAT2) * mTexCoords.size();
	desc.StructureByteStride = sizeof(XMFLOAT2);
	desc.InitialData = mTexCoords.data();

	if(mTexCoords.size() != 0)
		mTexCoordBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);
}

void Mesh::AllocateIndex()
{
	GraphicsBufferDesc desc;
	desc.ResourceUsage = ResourceUsage::DEFAULT;
	desc.Usage = BufferUsage::INDEX_BUFFER;
	desc.CPUAccess = BufferCPUAccess::NONE;
	desc.SizeInBytes = sizeof(uint16) * mIndices.size();
	desc.StructureByteStride = sizeof(uint16);
	desc.MiscFlags = 0;
	desc.InitialData = mIndices.data();

	if(mIndices.size() != 0)
		mIndexBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);
}