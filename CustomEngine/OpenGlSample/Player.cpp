#include "Player.h"

#include "include/GLFW/glfw3.h"

#include "Timer.h"
#include "Renderer.h"
#include "Cube.h"
#include "Camera.h"
#include "InputManager.h"

void Player::Init()
{
	SetMesh("suzanne.obj");
	SetTexture("suzanne.DDS");

	move = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);

	position = glm::vec3(0.0f, 0.0f, 0.0f);

	move = glm::translate(move, position);
	rot = glm::rotate(rot, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix = move * rot * ModelMatrix;

	LoadVBO();

	RenderableObject::Init();
}

void Player::Draw()
{
	RenderableObject::Draw();
}

void Player::Update()
{
	move = glm::mat4(1.0f);

	position = glm::vec3(0.0f, 0.0f, 0.0f);

	// Move forward
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		position += InputManager::Instance()->GetDirection() * move_speed;

	}
	// Move backward
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= InputManager::Instance()->GetDirection() * move_speed;
	}
	// Strafe right
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		position += InputManager::Instance()->GetRight() * move_speed;
	}
	// Strafe left
	if (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= InputManager::Instance()->GetRight() * move_speed;
	}

	camera->SetPositon(position);

	move = glm::translate(move, position);
	
	ModelMatrix = move * ModelMatrix;

	RenderableObject::Update();
}

void Player::End()
{
	RenderableObject::End();
}

