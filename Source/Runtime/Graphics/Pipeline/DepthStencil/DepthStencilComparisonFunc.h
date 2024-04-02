#pragma once

#include <Runtime/Core/Core.h>

enum class DepthStencilComparisonFunc : byte
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always
};
