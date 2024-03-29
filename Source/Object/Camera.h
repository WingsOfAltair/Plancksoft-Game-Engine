#pragma once

#include <GLFW/glfw3.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <cmath>

using namespace DirectX;

class Camera
{
public:
	Camera(XMFLOAT3 pos, XMINT2 windowSize) : mPosition(pos), mWindowSize(windowSize)
	{
		mView = XMMatrixIdentity();
		float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
		mProjection = XMMatrixPerspectiveFovLH(XM_PIDIV4, aspectRatio, 0.01f, 100.0f);
		mSpeed = 0.2f;
		mSensitivity = 100.0f;
	}

	void UpdateMatrix()
	{
		mView = XMMatrixLookAtLH(XMLoadFloat3(&mPosition), (XMLoadFloat3(&mOrientation) + XMLoadFloat3(&mPosition)),
			XMLoadFloat3(&mUp));
		mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(74.05f), (float)mWindowSize.x /
			(float)mWindowSize.y, 0.1f, 100.0f);
	}

	~Camera() = default;

	XMMATRIX GetViewMatrix() { return mView; }
	XMMATRIX GetProjectionMatrix() { return mProjection; }

	void HandleInputs(GLFWwindow* window)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				mPosition.x = mPosition.x + mSpeed * mOrientation.x;
				mPosition.y = mPosition.y + mSpeed * mOrientation.y;
				mPosition.z = mPosition.z + mSpeed * mOrientation.z;
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				mPosition.x = mPosition.x - mSpeed * mOrientation.x;
				mPosition.y = mPosition.y - mSpeed * mOrientation.y;
				mPosition.z = mPosition.z - mSpeed * mOrientation.z;
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp)));
				XMFLOAT3 rightFloat;
				XMStoreFloat3(&rightFloat, right);

				mPosition.x = mPosition.x + mSpeed * rightFloat.x;
				mPosition.y = mPosition.y + mSpeed * rightFloat.y;
				mPosition.z = mPosition.z + mSpeed * rightFloat.z;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp)));
				XMFLOAT3 rightFloat;
				XMStoreFloat3(&rightFloat, right);

				mPosition.x = mPosition.x - mSpeed * rightFloat.x;
				mPosition.y = mPosition.y - mSpeed * rightFloat.y;
				mPosition.z = mPosition.z - mSpeed * rightFloat.z;
			}

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				mPosition.x = mPosition.x + mSpeed * mUp.x;
				mPosition.y = mPosition.y + mSpeed * mUp.y;
				mPosition.z = mPosition.z + mSpeed * mUp.z;
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			{
				mPosition.x = mPosition.x - mSpeed * mUp.x;
				mPosition.y = mPosition.y - mSpeed * mUp.y;
				mPosition.z = mPosition.z - mSpeed * mUp.z;
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			{
				mSpeed = 0.4f;
			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
			{
				mSpeed = 0.1f;
			}
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (firstMouse)
			{
				glfwSetCursorPos(window, (double)(mWindowSize.x / 2), (double)(mWindowSize.y / 2));
				firstMouse = false;
			}

			double mouseX;
			double mouseY;

			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = mSensitivity * (float)(mouseY - (mWindowSize.y / 2)) / mWindowSize.y;
			float rotY = mSensitivity * (float)(-mouseX + (mWindowSize.x / 2)) / mWindowSize.x;

			XMFLOAT3 tempAxis;
			XMStoreFloat3(&tempAxis, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp))));

			XMFLOAT3 newOrientation = RotateVector(mOrientation, -rotX, tempAxis);

			if (abs(XMVectorGetX(XMVector3AngleBetweenNormals(XMLoadFloat3(&newOrientation), XMLoadFloat3(&mUp))) - XMConvertToRadians(90.0f)) <= XMConvertToRadians(85.0f))
			{
				mOrientation = newOrientation;
			}


			mOrientation = RotateVector(mOrientation, -rotY, mUp);

			glfwSetCursorPos(window, (mWindowSize.x / 2), (mWindowSize.y / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstMouse = true;
		}
	}

	void ProcessTransformPosition(GLFWwindow* window);
	void ProcessLookPosition(float xOffset, float yOffset) {}

private:
	XMFLOAT3 mPosition;
	XMFLOAT3 mOrientation = { 0.0f, 0.0f, -1.0f };
	XMFLOAT3 mUp = { 0.0f, 1.0f, 0.0f };

	XMINT2 mWindowSize;
	bool firstMouse = true;

	float mSpeed;
	float mSensitivity;

	XMMATRIX mView;
	XMMATRIX mProjection;

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