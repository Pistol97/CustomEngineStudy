#ifndef SHADER_H_
#define SHADER_H_

typedef unsigned int GLuint;

class Shader
{
public:
	Shader(const char* vertex_file_path, const char* fragment_file_path);
	GLuint LoadShaders();
private:
	const char* vertex_path;
	const char* fragment_path;
};

#endif // !SHADER_H_
