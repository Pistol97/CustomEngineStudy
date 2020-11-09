#include "Object.h"

#include "Renderer.h"

Object::Object()
{
	Renderer::Instance()->RegisterObject(this);
}