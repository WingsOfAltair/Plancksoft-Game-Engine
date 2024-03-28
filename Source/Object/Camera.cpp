#include "Camera.h"

void Camera::ProcessTransformPosition(GLFWwindow* window)
{
	float cameraSpeed = 0.1f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mPosition = { mPosition.x, mPosition.y, mPosition.z + cameraSpeed };
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mPosition = { mPosition.x, mPosition.y, mPosition.z - cameraSpeed };
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mPosition = { mPosition.x - cameraSpeed, mPosition.y, mPosition.z};
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mPosition = { mPosition.x + cameraSpeed, mPosition.y, mPosition.z };
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		mPosition = { mPosition.x, mPosition.y + cameraSpeed, mPosition.z };
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		mPosition = { mPosition.x, mPosition.y - cameraSpeed, mPosition.z };
	}
}