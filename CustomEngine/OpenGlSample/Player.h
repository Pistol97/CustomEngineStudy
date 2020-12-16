#ifndef PLAYER_H_
#define PLAYER_H_

#include "RenderableObject.h"

class Camera;

class Player : public RenderableObject
{
public:
	inline void SetCamera(Camera* cam) { camera = cam; }

protected:
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void End();

private:
	float move_speed = 0.1f;

	glm::mat4 move;

	glm::vec3 position;

	Camera* camera;
};

#endif // !PLAYER_H_
