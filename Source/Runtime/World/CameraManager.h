#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Singleton.h>
#include <Runtime/World/Camera.h>

#include <memory>


class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager()
	{
		if (mCamera == nullptr)
			mCamera = std::make_shared<Camera>();
	}
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	~CameraManager() = default;

	void Update()
	{
		mCamera->UpdateViewMatrix();
		mCamera->HandleInputs(WindowManager::GetInstance().GetWindow()->GetWindowHandle());
	}

	std::shared_ptr<Camera>& GetCamera() { return mCamera; }
private:
	std::shared_ptr<Camera> mCamera;
};
