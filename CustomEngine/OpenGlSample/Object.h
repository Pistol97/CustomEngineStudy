#ifndef OBJECT_H_
#define OBJECT_H_

#include "glm/glm.hpp"

#include "IClean.h"
#include "IUpdater.h"

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

//Component가 되는 오브젝트
class Object : public IClean, public IUpdater
{
public:
	Object();

	inline void Object_Init() { Init(); }
	inline void Object_Draw() { Draw(); }
	inline void Object_Update() { Update(); }
	inline void Object_End() { End(); }

	virtual void Clean() override {}
	virtual ~Object() {}

protected:
	virtual void Init() {}
	virtual void Draw() {}
	virtual void Update() override {}
	virtual void End() {}
};
#endif // !OBJECT_H_