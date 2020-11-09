#ifndef PLAYER_H_
#define PLAYER_H_

#include "RenderableObject.h"

class Player : public RenderableObject
{
public:
	void Move(glm::vec3 position);

public:
	inline float GetMoveSpeed() { return move_speed; }

protected:
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void End();

private:
	float move_speed = 10.0f;
};

#endif // !PLAYER_H_
