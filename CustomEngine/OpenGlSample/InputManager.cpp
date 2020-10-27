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

void InputManager::InputControl(Player* player)
{
	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);

	// Move forward
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) 
	{
		position += direction * Timer::Instance()->GetDeltaTime() * player->GetMoveSpeed();
		player->Move(position);
	}
	// Move backward
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) 
	{
		position -= direction * Timer::Instance()->GetDeltaTime() * player->GetMoveSpeed();
		player->Move(position);
	}
	// Strafe right
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) 
	{
		position += right * Timer::Instance()->GetDeltaTime() * player->GetMoveSpeed();
		player->Move(position);
	}
	// Strafe left
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) 
	{
		position -= right * Timer::Instance()->GetDeltaTime() * player->GetMoveSpeed();
		player->Move(position);
	}

	// For the next frame, the "last time" will be "now"
	Timer::Instance()->LateUpdate();
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