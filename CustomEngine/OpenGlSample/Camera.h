#ifndef CAMERA_H_
#define CAMERA_H_

#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;

class Camera
{

public:
	Camera(float x, float y, float z);

	void MouseView(GLFWwindow* window);

	inline glm::mat4 GetViewMatrix() const { return ViewMatrix; }

private:
	glm::vec3 position;

	glm::mat4 ViewMatrix;

	float speed = 3.0f;
	float mouseSpeed = 0.005f;
};

#endif // !CAMERA_H_

