#pragma once

#include <Runtime/Core/Core.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <DirectXMath.h>
using namespace DirectX;
#include <string>
#include <memory>

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window() = default;

	void ProcessMessage();

	XMINT2& GetPosition() noexcept { return mPosition; }
	XMUINT2& GetWindowSize() noexcept { return mWindowSize; }
	GLFWwindow* GetWindowHandle() noexcept { return mWindow; }
	HWND GetNativeWindowHandle() noexcept { return glfwGetWin32Window(mWindow); }

	bool IsOpen() const noexcept { return !glfwWindowShouldClose(mWindow); }
	bool IsFullscreen() const noexcept { return mIsFullscreen; }
private:
	std::string mTitle;
	XMINT2 mPosition;
	XMUINT2 mWindowSize;
	GLFWwindow* mWindow;
	bool mIsFullscreen;

};
