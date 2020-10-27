#include "NonRenderableObject.h"

#include "Renderer.h"

NonRenderableObject::NonRenderableObject()
{
	//생성과 동시에 렌더러에 자동등록
	Renderer::Instance()->RegisterNonRenderObject(this);
}

void NonRenderableObject::Update()
{

}
