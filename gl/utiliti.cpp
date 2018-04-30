#include "utiliti.h"

std::string readFile(const GLchar* path){
	FILE *file;
	fopen_s(&file, path, "r");

	fseek(file, 0, SEEK_END);
	const int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	GLchar* result = new GLchar[length+1];
	memset(result, 0, length+1);
	fread(result, sizeof(GLchar), sizeof(GLchar)* (length+1), file);
	result[length] = '\n';

	std::string resultStr(result);
	
	fclose(file);
	return resultStr;
}

GLint compileShader(const GLint shaderType, const GLchar* path){
	GLint shader = glCreateShader(shaderType);


	std::string vertexShaderSourceStr = readFile(path);

	const GLchar*  vertexShaderSource = vertexShaderSourceStr.c_str();


	glShaderSource(shader, 1, &(vertexShaderSource), NULL);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(shader);

		printf_s(&infoLog[0]);
	}



	return shader;
}