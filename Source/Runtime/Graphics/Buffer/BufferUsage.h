#pragma once

#include <Runtime/Core/Core.h>

enum class BufferUsage : byte
{
	UNKNOWN,
	VERTEX_BUFFER,
	INDEX_BUFFER,
	CONSTANT_BUFFER
};
