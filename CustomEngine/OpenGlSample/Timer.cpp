#include "Timer.h"

#include "include/GLFW/glfw3.h"

Timer* Timer::instance = nullptr;
double Timer::lastTime = NULL();

void Timer::Init()
{
	lastTime = glfwGetTime();

	fixedFrame = 60;

	QueryPerformanceFrequency(&hwInfo);
	QueryPerformanceCounter(&previous_frame);

	fps = hwInfo.QuadPart / fixedFrame;
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

bool Timer::IsUpdateTime()
{
	QueryPerformanceCounter(&current_frame);

	double renderTime = current_frame.QuadPart - previous_frame.QuadPart;

	if (renderTime > fps)
	{
		previous_frame = current_frame;

		return true;
	}

	return false;
}

void Timer::Clean()
{
	delete instance;
}
