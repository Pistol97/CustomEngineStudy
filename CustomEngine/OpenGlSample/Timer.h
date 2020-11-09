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
	
	void LateUpdate();

	virtual void Clean() override;

	bool IsRenderTime();
	bool IsUpdateTime();

public:
	inline float GetDeltaTime() { return deltaTime; }

protected:
	virtual void Init() override;
	virtual void Update() override;
	virtual void End() override;

private:
	Timer() {}
	~Timer() {}

	static Timer* instance;

	static double lastTime;
	double currentTime;
	float deltaTime;

	double fixed_frame;
	double max_frame;
	float fixed_fps;
	float max_fps;

	LARGE_INTEGER hwInfo;
	LARGE_INTEGER previous_frame;
	LARGE_INTEGER current_frame;
};

#endif // !TIMER_H_
