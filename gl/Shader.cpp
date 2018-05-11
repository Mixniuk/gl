#include "Shader.h"

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
	this->shaderProgram = compileShaderProgram(vertexSourcePath, fragmentSourcePath);
}


Shader::~Shader()
{
}
