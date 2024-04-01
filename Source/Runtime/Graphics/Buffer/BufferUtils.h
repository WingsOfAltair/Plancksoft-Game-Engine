#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Buffer/BufferCPUAccess.h>
#include <Runtime/Graphics/Buffer/BufferUsage.h>
#include <Runtime/Graphics/Buffer/ResourceUsage.h>

#include <d3d11.h>

class BufferUtils
{
public:
	static D3D11_BIND_FLAG GetBufferUsage(BufferUsage usage)
	{
		switch (usage)
		{
		case BufferUsage::UNKNOWN:
			return  D3D11_BIND_VERTEX_BUFFER;
		case BufferUsage::VERTEX_BUFFER:
			return  D3D11_BIND_VERTEX_BUFFER;
		case BufferUsage::INDEX_BUFFER:
			return D3D11_BIND_INDEX_BUFFER;
		case BufferUsage::CONSTANT_BUFFER:
			D3D11_BIND_CONSTANT_BUFFER;
		default:
			return D3D11_BIND_VERTEX_BUFFER;
		}
	}

	static uint32 GetBufferCPUAccess(BufferCPUAccess access)
	{
		switch (access)
		{
		case BufferCPUAccess::NONE:
			return 0;
		case BufferCPUAccess::READ:
			return D3D11_CPU_ACCESS_READ;
		case BufferCPUAccess::WRITE:
			return D3D11_CPU_ACCESS_WRITE;
		default:
			return 0;
		}
	}

	static D3D11_USAGE GetResourceUsage(ResourceUsage usage)
	{
		switch (usage)
		{
		case ResourceUsage::DEFAULT:
			return D3D11_USAGE_DEFAULT;
		case ResourceUsage::IMMUTABLE:
			return D3D11_USAGE_IMMUTABLE;
		case ResourceUsage::DYNAMIC:
			return D3D11_USAGE_DYNAMIC;
		case ResourceUsage::STAGING:
			return D3D11_USAGE_STAGING;
		default:
			return D3D11_USAGE_DEFAULT;
		}
	}
};
