#pragma once

#include <Runtime/Core/Core.h>

enum class ShaderResourceViewDimension : byte
{
	UNKNOWN,
	BUFFER,
	TEXTURE1D,
	TEXTURE1D_ARRAY,
	TEXTURE2D,
	TEXTURE2D_ARRAY,
	TEXTURE2D_MS,
	TEXTURE2D_MS_ARRAY,
	TEXTURE3D,
	TEXTURE_CUBE,
	TEXTURE_CUBE_ARRAY
};
