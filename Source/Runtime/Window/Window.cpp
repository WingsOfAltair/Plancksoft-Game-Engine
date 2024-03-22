#include "Window.h"

#include <Runtime/Graphics/Swapchain/Swapchain.h>

Window::Window()
{
	mWindowSize = { 1920, 1080 };
	mPosition = { 0, 0 };
	mTitle = "Rendering Engine";
	mIsFullscreen = false;

	DEV_ASSERT(glfwInit(), "Window", "Failed to initialize GLFW.");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	mWindow = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mTitle.c_str(), nullptr, nullptr);

	DEV_ASSERT(mWindow, "Window", "Failed to create window.");

	DEV_LOG(TE_VERBOSE, "Window", "Created window successfully.");
}

void Window::ProcessMessage()
{
	glfwPollEvents();
}
