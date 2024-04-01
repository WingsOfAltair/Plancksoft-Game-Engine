#pragma once

#include <Runtime/Core/Core.h>

enum class AddressMode : byte
{
    WRAP,
    MIRROR,
    CLAMP,
    BORDER,
    MIRROR_ONCE
};
