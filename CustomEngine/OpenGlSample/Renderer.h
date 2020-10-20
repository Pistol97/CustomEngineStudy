#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

#include "glm/glm.hpp"

#include "IClean.h"
#include "IUpdater.h"

struct GLFWwindow;

typedef unsigned int GLuint;

class RenderableObject;
class NonRenderableObject;
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
	void LoadVBO();
	void Draw();
	virtual void Update() override;
	virtual void Clean() override;

	inline void RegisterRenderObject(RenderableObject* object) { render_objects.push_back(object); }
	inline void RegisterNonRenderObject(NonRenderableObject* object) { non_render_objects.push_back(object); }
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

	std::vector<RenderableObject*> render_objects;
	std::vector<NonRenderableObject*> non_render_objects;

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
