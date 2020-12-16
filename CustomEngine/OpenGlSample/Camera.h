#ifndef CAMERA_H_
#define CAMERA_H_

#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;
class Player;

class Camera
{

public:
	Camera(float x, float y, float z);

	void MouseView(GLFWwindow* window);

	inline void SetPositon(glm::vec3 pos) { position += pos; }
	inline glm::mat4 GetViewMatrix() const { return ViewMatrix; }

	glm::vec3 position;

private:
	double mouse_xpos;
	double mouse_ypos;

	float mouse_speed = 0.01f;

	float horizontal_angle = 3.14f;
	float vertical_angle = 0.0f;

	glm::mat4 ViewMatrix;

	float speed = 3.0f;
	float mouseSpeed = 0.005f;
};

#endif // !CAMERA_H_

