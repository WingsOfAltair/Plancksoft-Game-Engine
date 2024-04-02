#pragma once

#include <Runtime/Core/Core.h>

enum class ShaderType : byte
{
	VERTEX_SHADER,
	PIXEL_SHADER,
	GEOMETRY_SHADER,
	HULL_SHADER,
	DOMAIN_SHADER,
	COMPUTE_SHADER
};
