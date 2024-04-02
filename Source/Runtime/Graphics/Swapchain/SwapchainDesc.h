#pragma once

#include <Runtime/Core/Core.h>

#include <memory>

#include <Runtime/Graphics/Texture/TextureFormat.h>

class Window;

struct SwapchainDesc
{
	std::shared_ptr<Window> Window;
	TextureFormat SwapchainFormat;
	uint32 BufferCount;
	uint32 TargetFrameRate;

};
