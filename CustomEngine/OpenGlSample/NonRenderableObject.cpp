#include "NonRenderableObject.h"

#include "Renderer.h"

NonRenderableObject::NonRenderableObject()
{
	//������ ���ÿ� �������� ���
	Renderer::Instance()->RegisterNonRenderObject(this);
}

void NonRenderableObject::Update()
{

}
