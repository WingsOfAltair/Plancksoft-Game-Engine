#include "Core.h"

#include <stdarg.h>
#include <stdlib.h>
#include <cassert>
#include <cstdio>

void DevAssert(bool condition, const char* pTitle, const char* pMessage, ...)
{
	if (!condition)
	{
		va_list args;
		va_start(args, pMessage);
		printf("\033[31m[%s]\033[39m -- ", pTitle);
		vprintf(pMessage, args);
		printf("\n");
		va_end(args);

		assert(condition);
	}
}

void DevLog(LogLevel level, const char* pTitle, const char* pMessage, ...)
{
	va_list args;
	va_start(args, pMessage);
	switch (level)
	{
	case LogLevel::Info:
		printf("\033[36m[%s]\033[39m -- ", pTitle);
		break;

	case LogLevel::Verbose:
		printf("\033[32m[%s]\033[39m -- ", pTitle);
		break;
	case LogLevel::Warning:
		printf("\033[33m[%s]\033[39m -- ", pTitle);
		break;
	case LogLevel::Error:
		printf("\033[31m[%s]\033[39m -- ", pTitle);
		break;
	case LogLevel::Fatal:
		printf("\033[35m[%s]\033[39m -- ", pTitle);
		break;
	default:
		break;
	}
	vprintf(pMessage, args);
	printf("\n");
	va_end(args);

	if (level == LogLevel::Fatal)
	{
		abort();
	}
}
