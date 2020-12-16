#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include "glm/gtc/matrix_transform.hpp"

#include "NonRenderableObject.h"

class Player;

class InputManager : public NonRenderableObject
{
public:
	static InputManager* Instance()
	{
		if (instance == nullptr)
		{
			instance = new InputManager();
		}
		return instance;
	}

	virtual void Update() override;
	virtual void Clean() override;


public:
	inline float GetHorizontalAngle() { return horizontal_angle; }
	inline float GetVerticaltalAngle() { return vertical_angle; }

	inline glm::vec3 GetDirection() { return direction; }
	inline glm::vec3 GetRight() { return right; }
	inline glm::vec3 GetUp() { return up; }


private:
	InputManager();
	~InputManager() {}
	static InputManager* instance;

	double mouse_xpos;
	double mouse_ypos;

	float mouse_speed = 0.001f;

	float horizontal_angle = 3.14f;
	float vertical_angle = 0.0f;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
};
#endif // !INPUTMANAGER_H_
