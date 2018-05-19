#include <SDL.h>
#include <stdio.h>
#include <string>
#include <glew.h>
#include <math.h>

#include "utiliti.h"

#define GLEW_STATIC
#define FPS 60.0f

bool work = true;
GLfloat vertices[] = {
	1.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,

	1.0f, -1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,

	-1.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,

	-1.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 1.0f,





	//second square
	0.75f, 0.75f, 0.0f,
	0.75f, -0.25f, 0.0f,
	-0.25f, -0.25f, 0.0f,
	-0.25, 0.75f, 0.0f, 

	//color

};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3,
	4, 5, 7,
	5, 6, 7
};

GLfloat color[] = {
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f
};


GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint vertexShader;
GLuint shaderProgram;
GLuint shaderProgramYellow;
GLfloat timeValue;
GLfloat greenValue;
GLfloat redValue;
GLint vertexColorLocation;
GLint mouseLocation;


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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat)* 3));// (sizeof(GLfloat)* 8));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	shaderProgram = compileShaderProgram("D:/WebGL/gl/shaders/first.vert", "D:/WebGL/gl/shaders/first.frag");
	shaderProgramYellow = compileShaderProgram("D:/WebGL/gl/shaders/first.vert", "D:/WebGL/gl/shaders/first_yellow.frag");
//	vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	vertexColorLocation = glGetUniformLocation(shaderProgram, "time");
	mouseLocation = glGetUniformLocation(shaderProgram, "mouseCorr");

	GLuint prevTime;
	GLuint currTime;
	while (work) {
		prevTime = SDL_GetTicks();

		glUseProgram(shaderProgram);

		while (SDL_PollEvent(&event)) {
			eventHandle(event);
		}

		timeValue = SDL_GetTicks();
		greenValue = ((sin(timeValue * 180 / M_PI) / 2) + 0.5);
		redValue = ((sin(timeValue * 180 / M_PI + 25) / 2) + 0.5);

		draw(window);

		currTime = SDL_GetTicks();
		GLfloat delay = (1 / FPS - (currTime - prevTime)) * 1000;
		if (delay > 0){
			SDL_Delay(delay);
		}
	}

	SDL_Quit();
	return 0; 
}

void draw(SDL_Window* window) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAO);
	

	glUniform1f(vertexColorLocation, timeValue);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glUseProgram(shaderProgramYellow);
	

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLuint)));


	glUseProgram(0);
	glBindVertexArray(0);
	SDL_GL_SwapWindow(window);
}

void eventHandle(SDL_Event& event) {
	switch (event.type)
	{
	case SDL_QUIT: work = false; break;
	case SDL_MOUSEMOTION: glUniform2f(mouseLocation, event.motion.x, event.motion.y); break;


	default:
		break;
	}
}