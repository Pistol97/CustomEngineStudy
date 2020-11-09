#include "Timer.h"

#include "include/GLFW/glfw3.h"

Timer* Timer::instance = nullptr;
double Timer::lastTime = NULL();

void Timer::Init()
{
	lastTime = glfwGetTime();

	fixed_frame = 30;
	max_frame = 300;

	QueryPerformanceFrequency(&hwInfo);
	QueryPerformanceCounter(&previous_frame);

	fixed_fps = hwInfo.QuadPart / fixed_frame;
	max_fps = hwInfo.QuadPart / max_frame;
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

void Timer::End()
{
}

void Timer::Clean()
{
	delete instance;
}

bool Timer::IsRenderTime()
{
	QueryPerformanceCounter(&current_frame);

	double renderTime = current_frame.QuadPart - previous_frame.QuadPart;

	if (renderTime > max_fps)
	{
		previous_frame = current_frame;

		return true;
	}

	return false;
}

bool Timer::IsUpdateTime()
{
	QueryPerformanceCounter(&current_frame);

	double renderTime = current_frame.QuadPart - previous_frame.QuadPart;

	if (renderTime > fixed_fps)
	{
		previous_frame = current_frame;

		return true;
	}

	return false;
}