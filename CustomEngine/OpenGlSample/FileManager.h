#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <vector>

#include "glm/glm.hpp"

typedef unsigned int GLuint;

class FileManager
{

public:
	static FileManager* Instance()
	{
		if (instance == nullptr)
		{
			instance = new FileManager();
		}

		return instance;
	}

	bool loadOBJ
	(
		const char* path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	GLuint loadDDS(const char* imagepath);

private:
	FileManager() {}
	~FileManager() {}
	static FileManager* instance;
};

#endif //FILEMANAGER_H_
