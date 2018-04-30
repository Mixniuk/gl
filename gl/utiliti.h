#ifndef _UTILITI_
#define _UTILITI_

#include<glew.h>
#include<stdio.h>
#include<string>
#include<vector>

std::string readFile(const GLchar* path);
GLint compileShader(const GLint shaderType, const GLchar* path);
#endif