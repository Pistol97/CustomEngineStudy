#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

#include "glm/glm.hpp"

#include "IClean.h"

struct GLFWwindow;

typedef unsigned int GLuint;

class RenderableObject;
class Camera;

class Renderer : public IClean
{
public:
	static Renderer* Instance()
	{
		if (instance == nullptr)
		{
			instance = new Renderer();
		}

		return instance;
	}

	void Init(int width, int height, const char* title_name);
	void LoadVBO();
	void Draw();
	virtual void Clean() override;

	inline void RegisterObject(RenderableObject* object) { objects.push_back(object); }
	inline GLFWwindow* GetWindow() { return window; }
	inline GLuint GetProgramID() { return programID; }

	inline void SetCamera(Camera* cam) { camera = cam; }

private:
	Renderer() {}
	~Renderer() {}

	static Renderer* instance;

	GLFWwindow* window;

	GLuint VertexArrayID;
	GLuint programID;

	std::vector<RenderableObject*> objects;

	GLuint TextureID;

	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	GLuint LightID;

	glm::mat4 ProjectionMatrix;

	glm::vec3 lightPos;

	Camera* camera;
};

#endif // RENDERER_H_
