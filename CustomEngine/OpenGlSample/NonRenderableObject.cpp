#include "NonRenderableObject.h"

#include "Renderer.h"

NonRenderableObject::NonRenderableObject()
{
	//������ ���ÿ� �������� �ڵ����
	Renderer::Instance()->RegisterNonRenderObject(this);
}

void NonRenderableObject::Update()
{

}
