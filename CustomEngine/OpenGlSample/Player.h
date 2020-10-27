#ifndef PLAYER_H_
#define PLAYER_H_

#include"glm/gtc/matrix_transform.hpp"

#include "RenderableObject.h"

class Player : public RenderableObject
{
public:
	Player(float _x, float _y, float _z);
	void Move(glm::vec3 position);

public:
	inline float GetMoveSpeed() { return move_speed; }
private:
	float move_speed = 10.0f;
};

#endif // !PLAYER_H_
