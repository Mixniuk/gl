#ifndef _UTILITI_
#define _UTILITI_

#include<glew.h>
#include<stdio.h>
#include<string>
#include<vector>

std::string readFile(const GLchar* path);
GLint compileShader(GLuint shaderType, GLchar* path);
GLint compileShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
#endif