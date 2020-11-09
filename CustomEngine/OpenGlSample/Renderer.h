#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

#include "glm/glm.hpp"

#include "IClean.h"
#include "IUpdater.h"

struct GLFWwindow;

typedef unsigned int GLuint;

class Object;
class RenderableObject;
class Camera;

class Renderer : public IClean, public IUpdater
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

	void Draw();
	virtual void Update() override;
	virtual void Clean() override;

	inline void RegisterObject(Object* object) { objects.push_back(object); }

	inline GLFWwindow* GetWindow() { return window; }
	inline GLuint GetTextureID() { return TextureID; }

	inline GLuint GetMatrixID() { return MatrixID; }
	inline GLuint GetViewMatrixID() { return ViewMatrixID; }
	inline GLuint GetModelMatrixID() { return ModelMatrixID; }
	inline glm::mat4 GetProjectionMatrix() { return ProjectionMatrix; }

	inline void SetCamera(Camera* cam) { camera = cam; }
	inline Camera* GetCamera() const { return camera; }

private:
	Renderer() {}
	~Renderer() {}

	static Renderer* instance;

	GLFWwindow* window;

	GLuint VertexArrayID;
	GLuint programID;

	std::vector<Object*> objects;

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
