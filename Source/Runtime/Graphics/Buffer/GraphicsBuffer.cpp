#include "GraphicsBuffer.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>

#include <Runtime/Graphics/Buffer/BufferUtils.h>

GraphicsBuffer::GraphicsBuffer(std::shared_ptr<GraphicsDevice> device, const GraphicsBufferDesc& desc)
{
	mOwnerDevice = device;
	mUsage = desc.Usage;
	mCPUAccess = desc.CPUAccess;
	mResourceUsage = desc.ResourceUsage;
	mMiscFlags = desc.MiscFlags;
	mSizeInBytes = desc.SizeInBytes;
	mStructureByteStride = (uint32)desc.StructureByteStride;

	D3D11_BUFFER_DESC bufferDesc;

	if (mSizeInBytes % 64 == 0) {
		bufferDesc.ByteWidth = mSizeInBytes;
	}
	else {
		bufferDesc.ByteWidth = mSizeInBytes + (64 - mSizeInBytes % 64);
	}

	bufferDesc.Usage = BufferUtils::GetResourceUsage(mResourceUsage);
	bufferDesc.BindFlags = BufferUtils::GetBufferUsage(mUsage);
	bufferDesc.CPUAccessFlags = BufferUtils::GetBufferCPUAccess(mCPUAccess);
	bufferDesc.MiscFlags = mMiscFlags;
	bufferDesc.StructureByteStride = (uint32)mStructureByteStride;

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = desc.InitialData;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateBuffer(&bufferDesc, &subresourceData, mBuffer.GetAddressOf())), "GraphicsBuffer",
				"Failed to create buffer.");

}
