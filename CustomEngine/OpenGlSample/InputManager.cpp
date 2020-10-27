#include "InputManager.h"

#include "include/GLFW/glfw3.h"

#include "Renderer.h"
#include "Timer.h"

InputManager* InputManager::instance = nullptr;

void InputManager::InputControl()
{
	//GLFW_KEY_W
	// Move forward
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * Timer::Instance()->GetDeltaTime() *move_speed;
	}
	// Move backward
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * Timer::Instance()->GetDeltaTime() * move_speed;
	}
	// Strafe right
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		position += right * Timer::Instance()->GetDeltaTime() * move_speed;
	}
	// Strafe left
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * Timer::Instance()->GetDeltaTime() * move_speed;
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
}

void InputManager::Clean()
{
	delete instance;
}
