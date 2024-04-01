#pragma once

#include <Runtime/Core/Core.h>

#include <string>

#include <Windows.h>

#define STRING(x) #x"/"
#define XSTRING(x) STRING(x)

class PlatformDirectory
{
public:
	static std::string GetExecutableDirectory()
	{
		char buffer[FILENAME_MAX];
		GetCurrentDirectory(FILENAME_MAX, buffer);
		std::string data = buffer;
		return data;
	}

	static std::string GetWorkingDirectory()
	{
		std::string workingDir = XSTRING(WORKING_ROOT);
		return workingDir;
	}

	static bool CopyFiles(const std::string& source, const std::string& destination)
	{
		return CopyFileA(source.c_str(), destination.c_str(), false);
	}

public:
	PlatformDirectory() = delete;
	~PlatformDirectory() = delete;
};
