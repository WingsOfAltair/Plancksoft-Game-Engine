#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Buffer/GraphicsBufferDesc.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class GraphicsBuffer : public GraphicsDeviceObject
{
public:
	GraphicsBuffer(std::shared_ptr<GraphicsDevice> device, const GraphicsBufferDesc& desc);
	virtual ~GraphicsBuffer() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::GraphicsBuffer; }

	ComPtr<ID3D11Buffer>& GetBuffer() { return mBuffer; }

	BufferUsage GetUsage() const noexcept { return mUsage; }
	BufferCPUAccess GetCPUAccess() const noexcept { return mCPUAccess; }
	ResourceUsage GetResourceUsage() const noexcept { return mResourceUsage; }
	uint8 GetMiscFlags() const noexcept { return mMiscFlags; }
	uint32 GetSizeInBytes() const noexcept { return mSizeInBytes; }
	uint32 GetStructureByteStride() const noexcept { return mStructureByteStride; }

private:
	BufferUsage mUsage;
	BufferCPUAccess mCPUAccess;
	ResourceUsage mResourceUsage;
	uint8 mMiscFlags;
	uint32 mSizeInBytes;
	uint32 mStructureByteStride;

	ComPtr<ID3D11Buffer> mBuffer;

};
