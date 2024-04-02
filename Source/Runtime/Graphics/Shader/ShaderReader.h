#pragma once

#include <Runtime/Core/Core.h>

#include <string>

#include <Runtime/Core/PlatformDirectory.h>

#include <Windows.h>

class ShaderReader
{
public:
	static std::string ReadShaderFile(const std::string& fileName)
	{
		std::string fullPath = PlatformDirectory::GetWorkingDirectory() + "\\Shaders\\" + fileName + ".hlsl";
	
		HANDLE fileHandle;
		DWORD countByte;

		fileHandle = CreateFileA(fullPath.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, nullptr);

		const DWORD fileSize = GetFileSize(fileHandle, nullptr);

		char* stringFile = new char[fileSize + 1];
		stringFile[fileSize] = '\0';

		if (ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr))
			return stringFile;
		else
			DEV_LOG(TE_FATAL, "ShaderReader", "Failed to read shader file.");

		delete[] stringFile;
		CloseHandle(fileHandle);

		return "";
	}

public:
	ShaderReader() = delete;
	ShaderReader(const ShaderReader&) = delete;
	ShaderReader& operator=(const ShaderReader&) = delete;
	~ShaderReader() = delete;
};
