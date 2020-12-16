#include "Camera.h"

#include "include/GLFW/glfw3.h"
#include "Timer.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Player.h"

Camera::Camera(float x, float y, float z)
{
	position = glm::vec3(x, y, z);

	//ī�޶� �ʱ� ����
	ViewMatrix = glm::lookAt(
		position,
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

void Camera::MouseView(GLFWwindow* window)
{
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + InputManager::Instance()->GetDirection(), // and looks here : at the same position, plus "direction"
		InputManager::Instance()->GetUp()                // Head is up (set to 0,-1,0 to look upside-down)
	);

	Timer::Instance()->LateUpdate();
}
