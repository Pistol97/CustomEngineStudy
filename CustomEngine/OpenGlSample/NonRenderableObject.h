#ifndef NONRENDERABLEOBJECT_H
#define NONRENDERABLEOBJECT_H

#include "Object.h"
#include "IUpdater.h"

class NonRenderableObject : public Object, public IUpdater
{
public:
	NonRenderableObject();
	virtual void Update() override;
};

#endif // !NONRENDERABLEOBJECT_H