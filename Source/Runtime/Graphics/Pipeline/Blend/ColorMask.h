#pragma once

#include <Runtime/Core/Core.h>

enum class ColorMask : byte
{
	Red = 1,
	Green = 2,
	Blue = 4,
	Alpha = 8,
	All = Red | Green | Blue | Alpha
};
