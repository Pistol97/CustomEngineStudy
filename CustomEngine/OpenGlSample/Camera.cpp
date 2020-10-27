#include "Camera.h"

#include "include/GLFW/glfw3.h"
#include "Timer.h"
#include "InputManager.h"

Camera::Camera(float x, float y, float z)
{
	position = glm::vec3(x, y, z);

	//카메라 초기 설정
	ViewMatrix = glm::lookAt(
		position,
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

void Camera::MouseView(GLFWwindow* window)
{
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(InputManager::Instance()->GetVerticaltalAngle()) * sin(InputManager::Instance()->GetHorizontalAngle()),
		sin(InputManager::Instance()->GetVerticaltalAngle()),
		cos(InputManager::Instance()->GetVerticaltalAngle()) * cos(InputManager::Instance()->GetHorizontalAngle())
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(InputManager::Instance()->GetHorizontalAngle() - 3.14f / 2.0f),
		0,
		cos(InputManager::Instance()->GetHorizontalAngle() - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	Timer::Instance()->LateUpdate();
}
