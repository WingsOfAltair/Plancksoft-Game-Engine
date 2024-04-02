#pragma once

#include <Runtime/Core/Core.h>

#include <DirectXMath.h>
using namespace DirectX;

#include <Runtime/Window/WindowManager.h>

class Camera
{
public:
	Camera()
	{
		mAspectRatio = (float)WindowManager::GetInstance().GetWindow()->GetWindowSize().x / (float)WindowManager::GetInstance().GetWindow()->GetWindowSize().y;
		mWindowSize = WindowManager::GetInstance().GetWindow()->GetWindowSize();
	}

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	~Camera() = default;

	void UpdateViewMatrix()
	{
		mView = XMMatrixLookAtLH(XMLoadFloat3(&mPosition), XMLoadFloat3(&mOrientation) + XMLoadFloat3(&mPosition), XMLoadFloat3(&mUp));
		mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(74.0f), mAspectRatio, 0.1f, 100.0f);
	}

	XMFLOAT3 GetPosition() { return mPosition; }
	XMMATRIX& GetViewMatrix() { return mView; }
	XMMATRIX& GetProjectionMatrix() { return mProjection; }

	void HandleInputs(GLFWwindow* api)
	{

		if (glfwGetMouseButton(api, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (glfwGetKey(api, GLFW_KEY_W) == GLFW_PRESS)
				mPosition = { mPosition.x + mOrientation.x * mSpeed, mPosition.y + mOrientation.y * mSpeed, mPosition.z + mOrientation.z * mSpeed };
			if (glfwGetKey(api, GLFW_KEY_S) == GLFW_PRESS)
				mPosition = { mPosition.x - mOrientation.x * mSpeed, mPosition.y - mOrientation.y * mSpeed, mPosition.z - mOrientation.z * mSpeed };
			if (glfwGetKey(api, GLFW_KEY_A) == GLFW_PRESS)
			{
				XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp)));
				XMFLOAT3 rightFloat;
				XMStoreFloat3(&rightFloat, right);
				mPosition = { mPosition.x + rightFloat.x * mSpeed, mPosition.y + rightFloat.y * mSpeed, mPosition.z + rightFloat.z * mSpeed };
			}
			if (glfwGetKey(api, GLFW_KEY_D) == GLFW_PRESS)
			{
				XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp)));
				XMFLOAT3 rightFloat;
				XMStoreFloat3(&rightFloat, right);
				mPosition = { mPosition.x - rightFloat.x * mSpeed, mPosition.y - rightFloat.y * mSpeed, mPosition.z - rightFloat.z * mSpeed };
			}
			if (glfwGetKey(api, GLFW_KEY_SPACE) == GLFW_PRESS)
				mPosition = { mPosition.x + mUp.x * mSpeed, mPosition.y + mUp.y * mSpeed, mPosition.z + mUp.z * mSpeed };
			if (glfwGetKey(api, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				mPosition = { mPosition.x - mUp.x * mSpeed, mPosition.y - mUp.y * mSpeed, mPosition.z - mUp.z * mSpeed };

			if (glfwGetKey(api, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				mSpeed = 0.5f;
			else if (glfwGetKey(api, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
				mSpeed = 0.1f;

			glfwSetInputMode(api, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );

			if (mFirstMouse)
			{
				glfwSetCursorPos(api, mWindowSize.x / 2.0f, mWindowSize.y / 2.0f);
				mFirstMouse = false;
			}

			double mouseX, mouseY;

			glfwGetCursorPos(api, &mouseX, &mouseY);

			float rotX = mSensitivity * (float)(mouseY - (mWindowSize.y / 2.0f)) / mWindowSize.y;
			float rotY = mSensitivity * (float)(-mouseX + (mWindowSize.x / 2.0f)) / mWindowSize.x;

			XMFLOAT3 tempAxis;
			XMStoreFloat3(&tempAxis, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp))));

			XMFLOAT3 tempOrientation = RotateVector(mOrientation, -rotX, tempAxis);

			if (abs(XMVectorGetX(XMVector3AngleBetweenNormals(XMLoadFloat3(&tempOrientation), XMLoadFloat3(&mUp))) - XMConvertToRadians(90.0f)) <= XMConvertToRadians(85.0f))
				mOrientation = tempOrientation;

			mOrientation = RotateVector(mOrientation, -rotY, mUp);

			glfwSetCursorPos(api, (mWindowSize.x / 2.0f), (mWindowSize.y / 2.0f));
		}
		else if (glfwGetMouseButton(api, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(api, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mFirstMouse = true;
		}
	}

private:
	XMFLOAT3 mPosition = { 0.0f, 0.0f, -3.0f };
	XMFLOAT3 mOrientation = { 0.0f, 0.0f, 1.0f };
	XMFLOAT3 mUp = { 0.0f, 1.0f, 0.0f };

	XMUINT2 mWindowSize;
	bool mFirstMouse = true;

	float mSpeed = 0.1f;
	float mSensitivity = 100.0f;
	float mAspectRatio = 0.0f;

	XMMATRIX mView = XMMatrixIdentity();
	XMMATRIX mProjection = XMMatrixIdentity();

	XMFLOAT3 RotateVector(XMFLOAT3 vector, float angle, XMFLOAT3 axis)
	{
		XMVECTOR xmVector = XMLoadFloat3(&vector);
		XMVECTOR xmAxis = XMLoadFloat3(&axis);
		XMMATRIX rotationMatrix = XMMatrixRotationAxis(xmAxis, XMConvertToRadians(angle));
		xmVector = XMVector3TransformCoord(xmVector, rotationMatrix);
		XMStoreFloat3(&vector, xmVector);
		return vector;
	}
};
