#include "include/GLFW/glfw3.h" 

#include "FileManager.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "Camera.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

int main(void)
{
	RenderableObject* cube = new RenderableObject();
	RenderableObject* suzanne = new RenderableObject(5.0f, 0.0f, 0.0f);

	Camera* camera = new Camera(0.0f, 1.0f, 15.0f);

	Renderer::Instance()->Init(1024, 768, "Custom Architecture");
	Renderer::Instance()->SetCamera(camera);

	//obj 불러오기
	cube->SetMesh("cube.obj");
	suzanne->SetMesh("suzanne.obj");

	//dds 불러오기
	cube->SetTexture("cube.DDS");
	suzanne->SetTexture("suzanne.DDS");

	Renderer::Instance()->LoadVBO();

	do {
		camera->computeMatricesFromInputs(Renderer::Instance()->GetWindow());

		Renderer::Instance()->Draw();
		Renderer::Instance()->Update();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(Renderer::Instance()->GetWindow()) == 0);

	Renderer::Instance()->Clean();

	delete cube;
	delete suzanne;
	delete camera;

	return 0;
}