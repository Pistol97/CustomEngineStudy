#include "RenderableObject.h"

#include "Renderer.h"
#include "FileManager.h"

#include "include/GL/glew.h"

#include "glm/gtc/matrix_transform.hpp"

RenderableObject::RenderableObject()
{
	//생성마다 Renderer에 Object 등록
	Renderer::Instance()->RegisterRenderObject(this);

	Texture = NULL;

	ModelMatrix = glm::mat4(1.0f);
}

RenderableObject::RenderableObject(float x, float y, float z)
{
	//생성마다 Renderer에 Object 등록
	Renderer::Instance()->RegisterRenderObject(this);

	Texture = NULL;

	ModelMatrix = glm::mat4(1.0f);
	glm::mat4 move = glm::mat4(1.0f);

	move = glm::translate(move, glm::vec3(x, y, z));

	ModelMatrix = move * ModelMatrix;

}

void RenderableObject::SetMesh(const char* path)
{
	FileManager::Instance()->loadOBJ(path, vertices, uvs, normals);
	indexVBO();
}

void RenderableObject::SetTexture(const char* path)
{
	Texture = FileManager::Instance()->loadDDS(path);
}

void RenderableObject::Clean()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);

	glDeleteTextures(1, &Texture);
}

void RenderableObject::indexVBO()
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