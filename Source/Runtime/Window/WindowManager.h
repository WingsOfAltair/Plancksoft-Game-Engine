#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Singleton.h>
#include <Runtime/Window/Window.h>

#include <memory>

class WindowManager : public Singleton<WindowManager>
{
public:
	WindowManager()
	{
		if (mWindow == nullptr)
			mWindow = std::make_shared<Window>();
	}
	~WindowManager() = default;

	std::shared_ptr<Window>& GetWindow() { return mWindow; }

private:
	std::shared_ptr<Window> mWindow;
};
