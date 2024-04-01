#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Singleton.h>
#include <Runtime/Application/Application.h>

#include <memory>

class ApplicationManager : public Singleton<ApplicationManager>
{
public:
	ApplicationManager()
	{
		if (mApplication == nullptr)
		{
			mApplication = std::make_shared<Application>();
			mApplication->Initialize();
		}
			
	}
	~ApplicationManager() = default;

	std::shared_ptr<Application>& GetApplication() { return mApplication; }

private:
	std::shared_ptr<Application> mApplication;
};
