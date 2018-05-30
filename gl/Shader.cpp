#include "Shader.h"

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
	this->shaderProgram = compileShaderProgram(vertexSourcePath, fragmentSourcePath);
}

void Shader::use(){
	glUseProgram(this->shaderProgram);
}

Shader::~Shader()
{
	glDeleteProgram(this->shaderProgram);
}

Shader::operator GLuint(){
	return this->shaderProgram;
}
