#include "Cube.h"

void Cube::Init()
{
	SetMesh("cube.obj");
	SetTexture("cube.DDS");

	glm::mat4 move = glm::mat4(1.0f);

	move = glm::translate(move, glm::vec3(3.0f, -1.0f, 2.0f));

	ModelMatrix = move * ModelMatrix;

	LoadVBO();
}

void Cube::Draw()
{
	RenderableObject::Draw();
}

void Cube::Update()
{
}

void Cube::End()
{
}
