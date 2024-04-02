#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Texture/TextureFormat.h>
#include <Runtime/Graphics/Texture/ShaderResourceViewDimension.h>

class Texture;

struct TextureViewDesc
{
	TextureFormat Format;
	ShaderResourceViewDimension SRVDimension;
	uint32 MostDetailedMip;
	uint32 MipLevels;

	Texture* pTexture;
};
