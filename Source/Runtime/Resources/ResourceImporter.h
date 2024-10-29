#pragma once

#include <Runtime/Core/Core.h>

#include <string>
#include <memory>	   
#include <filesystem>

class Mesh;
class TextureResource;

class ResourceImporter
{
public:
	ResourceImporter() = delete;
	~ResourceImporter() = delete;

	static std::string GetAbsolutePath();
	static void ReadStaticMeshFile(const std::string& absolutePath, std::shared_ptr<Mesh> mesh);
	static void ReadTextureFile(const std::string& absolutePath, std::shared_ptr<TextureResource> texture);
};
