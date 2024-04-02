#pragma once

#include <Runtime/Core/Core.h>

enum class ResourceUsage : byte
{
	DEFAULT,
	IMMUTABLE,
	DYNAMIC,
	STAGING
};
