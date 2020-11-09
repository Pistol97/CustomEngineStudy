#ifndef CUBE_H_
#define CUBE_H_

#include "RenderableObject.h"

class Cube : public RenderableObject
{
protected:
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void End();
};
#endif // !CUBE_H_
