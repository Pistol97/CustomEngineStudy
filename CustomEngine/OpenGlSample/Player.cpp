#include "Player.h"

#include "Timer.h"

Player::Player(float x, float y, float z) : RenderableObject(x, y, z)
{

}

void Player::Move(glm::vec3 position)
{
	glm::mat4 move = glm::mat4(1.0f);

	move = glm::translate(move, position);

	ModelMatrix = move * ModelMatrix;
}

