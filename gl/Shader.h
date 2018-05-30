#ifndef _SHADER_
#define _SHADER_

#include "utiliti.h"
#include <glew.h>

class Shader
{
public:
	GLuint shaderProgram;
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	~Shader();

	operator GLuint();

	void use();
};

#endif