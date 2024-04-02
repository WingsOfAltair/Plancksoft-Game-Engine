#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Shader/ShaderType.h>

#include <string>

struct ShaderDesc
{
	std::string EntryPoint;
	std::string ShaderName;
	std::string ShaderModel;
	ShaderType Type;
};
