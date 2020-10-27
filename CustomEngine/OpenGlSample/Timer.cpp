#include "Timer.h"

#include "include/GLFW/glfw3.h"

Timer* Timer::instance = nullptr;
double Timer::lastTime = NULL();

void Timer::Init()
{
	lastTime = glfwGetTime();
}

void Timer::Update()
{
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
}

void Timer::LateUpdate()
{
	lastTime = currentTime;
}

void Timer::Clean()
{
	delete instance;
}
