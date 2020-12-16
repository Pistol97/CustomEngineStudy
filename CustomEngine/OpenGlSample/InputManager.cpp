#include "InputManager.h"

#include <iostream>
#include "include/GLFW/glfw3.h"

#include "Renderer.h"
#include "Timer.h"
#include "Player.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
}

void InputManager::Update()
{
	// 커서 위치 불러오기
	glfwGetCursorPos(Renderer::Instance()->GetWindow(), &mouse_xpos, &mouse_ypos);

	// 해상도에 맞춰 다음 프레임을 위한 커서 위치 초기화
	glfwSetCursorPos(Renderer::Instance()->GetWindow(), 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontal_angle += mouse_speed * float(1024 / 2 - mouse_xpos);
	vertical_angle += mouse_speed * float(768 / 2 - mouse_ypos);

	direction = glm::vec3(
		cos(vertical_angle) * sin(horizontal_angle),
		sin(vertical_angle),
		cos(vertical_angle) * cos(horizontal_angle)
	);

	right = glm::vec3(
		sin(horizontal_angle - 3.14f / 2.0f),
		0,
		cos(horizontal_angle - 3.14f / 2.0f)
	);

	up = glm::cross(right, direction);
}

void InputManager::Clean()
{
	delete instance;
}