#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <string>

struct WindowSize
{
	int X, Y;
};

class Window
{
public:
	Window(WindowSize size, const std::string& title);
	~Window();

	void Initialize();
	void Run();

	bool IsVisible() const { return !glfwWindowShouldClose(mWindow); }
	GLFWwindow* GetWindowHandler() const { return mWindow; }
	HWND GetWindowNativeHandler() const { return glfwGetWin32Window(mWindow); }
	WindowSize GetSize() const { return mSize; }
private:
	GLFWwindow* mWindow;
	WindowSize mSize;
	std::string mTitle;

};
