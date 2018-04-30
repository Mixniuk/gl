#include<SDL.h>
#include<stdio.h>
#include <string>
#include<glew.h>

#include "utiliti.h"

#define GLEW_STATIC

bool work = true;
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

GLuint VBO;
GLuint vertexShader;
GLuint shaderProgram;

void eventHandle(SDL_Event& event);
void draw(SDL_Window* window);

int main(int argc, char** args) {
	SDL_Window* window = nullptr;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("dranik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_Event event;

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	glewInit();

	
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClearDepth(1.0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint vertexShader = compileShader(GL_VERTEX_SHADER, "D:/WebGL/gl/shaders/first.vert");
	GLint fragmentShader = compileShader(GL_FRAGMENT_SHADER, "D:/WebGL/gl/shaders/first.frag");
	shaderProgram = glCreateProgram();

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);




	while (work) {
		while (SDL_PollEvent(&event)) {
			eventHandle(event);
		}


		draw(window);


	}
	

	SDL_Quit();
	
	return 0; 
}

void draw(SDL_Window* window) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);

	glDrawArrays(GL_TRIANGLES, 0, 3);


	glUseProgram(0);
	SDL_GL_SwapWindow(window);
}

void eventHandle(SDL_Event& event) {
	switch (event.type)
	{
	case SDL_QUIT: work = false; break;

	default:
		break;
	}
}