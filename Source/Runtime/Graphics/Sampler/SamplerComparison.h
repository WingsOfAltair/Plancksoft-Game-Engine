#pragma once

#include <Runtime/Core/Core.h>

enum class SamplerComparison : byte
{
    NEVER,
    LESS,
    EQUAL,
    LESS_EQUAL,
    GREATER,
    NOT_EQUAL,
    GREATER_EQUAL,
    ALWAYS
};
