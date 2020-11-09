#include "Player.h"

#include "Timer.h"

void Player::Init()
{
	SetMesh("suzanne.obj");
	SetTexture("suzanne.DDS");

	glm::mat4 move = glm::mat4(1.0f);

	move = glm::translate(move, glm::vec3(0.0f, 0.0f, 0.0f));

	ModelMatrix = move * ModelMatrix;

	LoadVBO();
}

void Player::Draw()
{
	Render();
}

void Player::Update()
{
}

void Player::End()
{
}

void Player::Move(glm::vec3 position)
{
	glm::mat4 move = glm::mat4(1.0f);

	move = glm::translate(move, position);

	ModelMatrix = move * ModelMatrix;
}

