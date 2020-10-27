#include "include/GLFW/glfw3.h" 

#include "FileManager.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "Timer.h"
#include "InputManager.h"
#include "Camera.h"
#include "Player.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

int main(void)
{
	RenderableObject* cube = new RenderableObject(0.0f, 0.0f, 0.0f);
	Player* player = new Player(0.0f, -3.0f, 9.0f);

	Camera* camera = new Camera(0.0f, 1.0f, 15.0f);

	Renderer::Instance()->Init(1024, 768, "Custom Architecture");
	Renderer::Instance()->SetCamera(camera);

	//obj 불러오기
	cube->SetMesh("cube.obj");
	player->SetMesh("suzanne.obj");

	//dds 불러오기
	cube->SetTexture("cube.DDS");
	player->SetTexture("suzanne.DDS");

	Renderer::Instance()->LoadVBO();
	Timer::Instance()->Init();

	player->Rotate(180.0f);

	do {

		Renderer::Instance()->Update();
		Renderer::Instance()->Draw();
		camera->MouseView(Renderer::Instance()->GetWindow());
		InputManager::Instance()->InputControl(player);
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(Renderer::Instance()->GetWindow()) == 0);

	Renderer::Instance()->Clean();
	Timer::Instance()->Clean();
	InputManager::Instance()->Clean();

	delete cube;
	delete player;
	delete camera;

	return 0;
}