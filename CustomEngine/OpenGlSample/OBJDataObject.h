#ifndef OBJDATAOBJECT_H
#define OBJDATAOBJECT_H

#include "Object.h"

class OBJDataObject : public UnRenderableObject
{
public:
	void PrintDatas();
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};

#endif // !OBJDATAOBJECT_H