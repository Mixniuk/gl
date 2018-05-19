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

GLint compileShader(GLuint shaderType, const GLchar* path) {
	GLint shader = glCreateShader(shaderType);

	std::string shaderSourceStr = readFile(path);

	const GLchar*  shaderSource = shaderSourceStr.c_str();

	glShaderSource(shader, 1, &(shaderSource), nullptr);
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

GLint compileShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath){
	GLint vertexShader = compileShader(GL_VERTEX_SHADER, vertexPath);
	GLint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentPath);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint isCompiled = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteProgram(shaderProgram);

		printf_s(&infoLog[0]);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return shaderProgram;
}