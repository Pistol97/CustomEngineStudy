#include "include/GLFW/glfw3.h" 

#include "FileManager.h"
#include "Renderer.h"
#include "Timer.h"
#include "InputManager.h"
#include "Camera.h"

#include "RenderableObject.h"
#include "Player.h"
#include "Cube.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

int main(void)
{
	Camera* camera = new Camera(0.0f, 1.0f, 15.0f);

	RenderableObject* cube = new Cube();
	RenderableObject* player = new Player();

	player->AddObject(cube);
	Renderer::Instance()->RegisterObject(player);

	Renderer::Instance()->Init(1024, 768, "Custom Architecture");
	Renderer::Instance()->SetCamera(camera);

	while (glfwGetKey(Renderer::Instance()->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(Renderer::Instance()->GetWindow()) == 0)
	{
		//최대 300프레임
		if (Timer::Instance()->IsRenderTime())
		{
			Renderer::Instance()->Draw();
;		}

		//최대 30프레임
		if (Timer::Instance()->IsUpdateTime())
		{
			//InputManager::Instance()->InputControl(player);
			Renderer::Instance()->Update();
		}

		//camera->MouseView(Renderer::Instance()->GetWindow());
	}

	Renderer::Instance()->Clean();

	delete player;
	delete camera;

	return 0;
}