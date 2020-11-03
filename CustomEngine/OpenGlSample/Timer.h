#ifndef TIMER_H_
#define TIMER_H_

#include "NonRenderableObject.h"

#include <Windows.h>


class Timer : public NonRenderableObject
{
public:
	static Timer* Instance()
	{
		if (instance == nullptr)
		{
			instance = new Timer();
		}
		return instance;
	}
	
	void Init();
	virtual void Update() override;
	void LateUpdate();

	bool IsUpdateTime();

	virtual void Clean() override;

public:
	inline float GetDeltaTime() { return deltaTime; }

private:
	Timer() {}
	~Timer() {}

	static Timer* instance;

	static double lastTime;
	double currentTime;
	float deltaTime;

	double fixedFrame;
	float fps;

	LARGE_INTEGER hwInfo;
	LARGE_INTEGER previous_frame;
	LARGE_INTEGER current_frame;
};

#endif // !TIMER_H_
