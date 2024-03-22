#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Singleton.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>

class GraphicsManager : public Singleton<GraphicsManager>
{
public:
	GraphicsManager()
	{
		if(mMainDevice == nullptr)
			mMainDevice = std::make_shared<GraphicsDevice>();
	}
	~GraphicsManager() = default;

	std::shared_ptr<GraphicsDevice>& GetMainDevice() { return mMainDevice; }

private:
	std::shared_ptr<GraphicsDevice> mMainDevice;
};
