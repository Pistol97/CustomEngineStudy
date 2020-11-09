#ifndef RENDERABLEOBJECT_H_
#define	RENDERABLEOBJECT_H_

#include <map>
#include <vector>

#include"glm/gtc/matrix_transform.hpp"

#include "Object.h"

class RenderableObject : public Object
{
public:
	RenderableObject();

	virtual void Clean() override;

protected:
	virtual void Init() {}
	virtual void Update() override {}
	virtual void Draw() {}
	virtual void End() {}

	void IndexVBO();
	void LoadVBO();

	void SetMesh(const char* path);
	void SetTexture(const char* path);
	void Rotate(float degree);

	void Render();

	bool getSimilarVertexIndex_fast
	(
		PackedVertex& packed,
		std::map<PackedVertex, unsigned short>& VertexToOutIndex,
		unsigned short& result
	);

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
};
#endif // RENDERABLEOBJECT_H_