#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include "glm/gtc/matrix_transform.hpp"

#include "NonRenderableObject.h"

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

	void InputControl();

	virtual void Update() override;
	virtual void Clean() override;
	

public:
	inline float GetHorizontalAngle() { return horizontal_angle; }
	inline float GetVerticaltalAngle() { return vertical_angle; }

private:
	InputManager() {}
	~InputManager() {}
	static InputManager* instance;

	double mouse_xpos;
	double mouse_ypos;

	float mouse_speed = 0.005f;
	float move_speed = 3.0f;

	float horizontal_angle = 3.14f;
	float vertical_angle = 0.0f;

	glm::vec3 position;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
};


#endif // !INPUTMANAGER_H_
