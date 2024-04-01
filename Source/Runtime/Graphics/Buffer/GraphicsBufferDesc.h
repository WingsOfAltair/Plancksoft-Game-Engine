#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Buffer/BufferUsage.h>
#include <Runtime/Graphics/Buffer/BufferCPUAccess.h>
#include <Runtime/Graphics/Buffer/ResourceUsage.h>


struct GraphicsBufferDesc
{
	BufferUsage Usage;
	BufferCPUAccess CPUAccess;
	ResourceUsage ResourceUsage;
	uint8 MiscFlags;
	uint32 SizeInBytes;
	uint64 StructureByteStride;

	void* InitialData;
};
