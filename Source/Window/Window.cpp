#include "Window.h"

Window::Window(WindowSize size, const std::string& title) : mSize(size), mTitle(title)
{

}

Window::~Window()
{
	glfwTerminate();
}

void Window::Initialize()
{
	if (!glfwInit())
		printf("Failed to initialize GLFW.\n");
	else printf("GLFW initialized successfully.\n");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);	+
	printf("GLFW No Client API.\n");
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	printf("GLFW Not Resizable.\n");

	mWindow = glfwCreateWindow(mSize.X, mSize.Y, mTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	printf("GLFW Created Window Successfully.\n");
}

void Window::Run()
{
	glfwPollEvents();
}