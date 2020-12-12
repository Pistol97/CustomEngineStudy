#include "RenderableObject.h"

#include "Renderer.h"
#include "FileManager.h"
#include "Camera.h"

#include "include/GL/glew.h"

#include "glm/gtc/matrix_transform.hpp"

RenderableObject::RenderableObject()
{
	Texture = NULL;

	ModelMatrix = glm::mat4(1.0f);

	table = new std::vector<Object*>();
;}

RenderableObject::~RenderableObject()
{
	for (std::vector<Object*>::iterator it = table->begin();
		it != table->end();
		++it)
	{
		delete (*it);
	}

	table->clear();

	delete table;
}

void RenderableObject::AddObject(Object* obj)
{
	table->push_back(obj);
}

void RenderableObject::Clean()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);

	glDeleteTextures(1, &Texture);
}

void RenderableObject::Init()
{
	for (
		std::vector<Object*>::const_iterator it = table->begin();
		it != table->end();
		++it
		)
	{
		(*it)->Object_Init();
	}
}

void RenderableObject::Update()
{
	for (
		std::vector<Object*>::const_iterator it = table->begin();
		it != table->end();
		++it
		)
	{
		(*it)->Object_Update();
	}
}

void RenderableObject::Draw()
{	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Renderer::Instance()->GetTextureID(), 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glUniformMatrix4fv(Renderer::Instance()->GetViewMatrixID(), 1, GL_FALSE, &Renderer::Instance()->GetCamera()->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(Renderer::Instance()->GetModelMatrixID(), 1, GL_FALSE, &ModelMatrix[0][0]);
	glm::mat4 MVP = Renderer::Instance()->GetProjectionMatrix() * Renderer::Instance()->GetCamera()->GetViewMatrix() * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(Renderer::Instance()->GetMatrixID(), 1, GL_FALSE, &MVP[0][0]);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,
		indices.size(),
		GL_UNSIGNED_INT,
		(void*)0
	);

	for (
		std::vector<Object*>::const_iterator it = table->begin();
		it != table->end();
		++it
		)
	{
		(*it)->Object_Draw();
	}
}

void RenderableObject::End()
{
	for (
		std::vector<Object*>::const_iterator it = table->begin();
		it != table->end();
		++it
		)
	{
		(*it)->Object_End();
	}
}

void RenderableObject::IndexVBO()
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < vertices.size(); i++) {

		PackedVertex packed = { vertices[i], uvs[i], normals[i] };

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			indexed_vertices.push_back(vertices[i]);
			indexed_uvs.push_back(uvs[i]);
			indexed_normals.push_back(normals[i]);
			unsigned short newindex = (unsigned short)indexed_vertices.size() - 1;
			indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

void RenderableObject::LoadVBO()
{
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void RenderableObject::SetMesh(const char* path)
{
	FileManager::Instance()->loadOBJ(path, vertices, uvs, normals);
	IndexVBO();
}

void RenderableObject::SetTexture(const char* path)
{
	Texture = FileManager::Instance()->loadDDS(path);
}

void RenderableObject::Rotate(float degree)
{
	glm::mat4 rotation = glm::mat4(1.0f);

	rotation = glm::rotate(rotation, glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix = ModelMatrix * rotation;
}

void RenderableObject::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Renderer::Instance()->GetTextureID(), 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glUniformMatrix4fv(Renderer::Instance()->GetViewMatrixID(), 1, GL_FALSE, &Renderer::Instance()->GetCamera()->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(Renderer::Instance()->GetModelMatrixID(), 1, GL_FALSE, &ModelMatrix[0][0]);
	glm::mat4 MVP = Renderer::Instance()->GetProjectionMatrix() * Renderer::Instance()->GetCamera()->GetViewMatrix() * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(Renderer::Instance()->GetMatrixID(), 1, GL_FALSE, &MVP[0][0]);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,
		indices.size(),
		GL_UNSIGNED_INT,
		(void*)0
	);
}

bool RenderableObject::getSimilarVertexIndex_fast(PackedVertex& packed,
	std::map<PackedVertex, unsigned short>& VertexToOutIndex,
	unsigned short& result)
{
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end())
	{
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}