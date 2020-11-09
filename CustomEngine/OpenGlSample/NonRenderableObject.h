#ifndef NONRENDERABLEOBJECT_H
#define NONRENDERABLEOBJECT_H

#include "Object.h"

class NonRenderableObject : public Object
{
public:
	virtual void Init() {}
	virtual void Update() override {}
	virtual void End() {}

	virtual void Clean() override {}
};

#endif // !NONRENDERABLEOBJECT_H