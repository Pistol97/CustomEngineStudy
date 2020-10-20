#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include <map>

#include "glm/glm.hpp"

#include "IClean.h"

typedef unsigned int GLuint;

struct PackedVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const
	{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

class Object : public IClean
{
public:
	virtual ~Object() {}
};
#endif // !OBJECT_H_