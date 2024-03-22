#pragma once

#include <Runtime/Core/Core.h>

#include <memory>

class Window;
class GraphicsDevice;
class Swapchain;
class Framebuffer;
class CommandList;

class Application
{
public:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	virtual ~Application() = default;

	void Initialize();
	void Run();

	bool IsRunning();

	std::shared_ptr<CommandList>& GetCommandList() { return mCommandList; }

private:
	std::shared_ptr<Window> mWindow;
	std::shared_ptr<GraphicsDevice> mGraphicsDevice;
	std::shared_ptr<Swapchain> mSwapchain;
	std::shared_ptr<Framebuffer> mFramebuffer;

	std::shared_ptr<CommandList> mCommandList;
};
