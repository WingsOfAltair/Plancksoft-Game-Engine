#pragma once

typedef unsigned char uint8, byte;
typedef unsigned short uint16, word;
typedef unsigned int uint32, dword;
typedef unsigned long long uint64, qword;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef float float32;
typedef double float64;

#define uint64_max 0xFFFFFFFFFFFFFFFF

enum class LogLevel
{
	Info,
	Verbose,
	Warning,
	Error,
	Fatal

};

void DevAssert(bool condition, const char* pTitle, const char* pMessage, ...);
void DevLog(LogLevel level, const char* pTitle, const char* pMessage, ...);

#define TE_INFO LogLevel::Info
#define TE_VERBOSE LogLevel::Verbose
#define TE_WARNING LogLevel::Warning
#define TE_ERROR LogLevel::Error
#define TE_FATAL LogLevel::Fatal

#ifdef TUTORIAL_DEBUG
#define DEV_ASSERT(condition, pTitle, pMessage, ...) DevAssert(condition, pTitle, pMessage, __VA_ARGS__)
#define DEV_LOG(level, pTitle, pMessage, ...) DevLog(level, pTitle, pMessage, __VA_ARGS__)
#else
#define DEV_ASSERT(condition, pTitle, pMessage, ...) (condition)
#endif

#define FloatMax 3.402823466e+38F
