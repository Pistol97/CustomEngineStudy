#ifndef TIMER_H_
#define TIMER_H_

#include "NonRenderableObject.h"

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
	void Update();
	void LateUpdate();
	void Clean();

public:
	inline float GetDeltaTime() { return deltaTime; }

private:
	Timer() {}
	~Timer() {}

	static Timer* instance;

	static double lastTime;
	double currentTime;
	float deltaTime;
};

#endif // !TIMER_H_
