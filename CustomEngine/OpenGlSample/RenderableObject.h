#ifndef RENDERABLEOBJECT_H
#define	RENDERABLEOBJECT_H

#include "Object.h"

class RenderableObject : public Object
{
public:
	//해당 좌표 생성
	RenderableObject(float x, float y, float z);

	void SetMesh(const char* path);
	void SetTexture(const char* path);
	void Rotate(float degree);

	virtual void Clean() override;


public:
	inline std::vector<glm::vec3>& GetIndexedVertices() { return indexed_vertices; }
	inline std::vector<glm::vec2>& GetIndexedUVs() { return indexed_uvs; }
	inline std::vector<glm::vec3>& GetIndexedNormals() { return indexed_normals; }
	inline std::vector<unsigned int>& GetIndices() { return indices; }

	inline GLuint& GetVertexBuffer() { return vertexbuffer; }
	inline GLuint& GetUVBuffer() { return uvbuffer; }
	inline GLuint& GetNormalBuffer() { return normalbuffer; }
	inline GLuint& GetElementBuffer() { return elementbuffer; }

	inline GLuint& GetTexture() { return Texture; }
	inline glm::mat4 GetModelMatrix() const { return ModelMatrix; }

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<unsigned int> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

	GLuint Texture;

	glm::mat4 ModelMatrix;

	void indexVBO();

	bool getSimilarVertexIndex_fast
	(
		PackedVertex& packed,
		std::map<PackedVertex, unsigned short>& VertexToOutIndex,
		unsigned short& result
	);
};

#endif