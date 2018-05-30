#include <SDL.h>
#include <stdio.h>
#include <string>
#include <glew.h>
#include <math.h>
#include <vec3.hpp>
#include <vec2.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stddef.h>
#include <time.h>

#include "../Source/OBJ_Loader.h"
#include "Shader.h"
#include "utiliti.h"

#define GLEW_STATIC
#define FPS 60.0f

struct Position
{
	float x;
	float y;
	float z;
};

struct Color
{
	float r;
	float g;
	float b;
};

struct Verticices
{
	Position position;
	Color color;
};

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
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3,
};

GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint vertexShader;
Shader* shaderProgram;
GLfloat timeValue;
GLfloat greenValue;
GLfloat redValue;
GLint vertexColorLocation;
GLint transformLocation;
GLint projLocation;
GLint mouseLocation;
GLchar* path3d;

std::vector< Verticices > out_vertices;

glm::mat4 scalingMatrix; 
glm::mat4 translateMat;
glm::mat4 rotateMat;
glm::mat4 transformMat; 
glm::mat4 projMat;

void eventHandle(SDL_Event& event);
void draw(SDL_Window* window);

int main(int argc, char** args) {
	SDL_Window* window = nullptr;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("dranik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_Event event;

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);

	path3d = "D:/WebGL/gl/models/247_House_15_obj.obj";

	objl::Loader loader;
	loader.LoadFile(path3d);
	std::vector< objl::Vertex > vetrexObj = loader.LoadedVertices;

	srand(time(NULL));
	for (int i = 0; i < vetrexObj.size(); i++){
		Verticices vertex;
		vertex.position.x = vetrexObj[i].Position.X;
		vertex.position.y = vetrexObj[i].Position.Y;
		vertex.position.z = vetrexObj[i].Position.Z;
		vertex.color.r = (rand() % 100 + 1) / 100.0f;
		vertex.color.g = (rand() % 100 + 1) / 100.0f;
		vertex.color.b = (rand() % 100 + 1) / 100.0f;
		out_vertices.push_back(vertex);
	}

	scalingMatrix = glm::scale(glm::mat4x4(1.0f), glm::vec3(0.004f, 0.004f, 0.004f));
	translateMat = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
	rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transformMat = translateMat * rotateMat * scalingMatrix; //translation rotation scale
	projMat = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(Verticices), &out_vertices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Verticices), (GLvoid*)offsetof(Verticices, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Verticices), (GLvoid*)offsetof(Verticices, color));// (sizeof(GLfloat)* 8));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaderProgram = new Shader("D:/WebGL/gl/shaders/first.vert", "D:/WebGL/gl/shaders/first.frag");

	vertexColorLocation = glGetUniformLocation(shaderProgram->shaderProgram, "time");
	mouseLocation = glGetUniformLocation(shaderProgram->shaderProgram, "mouseCorr");
	transformLocation = glGetUniformLocation(shaderProgram->shaderProgram, "transform");
	projLocation = glGetUniformLocation(shaderProgram->shaderProgram, "proj");

	GLuint prevTime;
	GLuint currTime;
	GLuint cycles = 1, elapsedTime = 0;
	GLuint rotate = 0;

	while (work) {
		prevTime = SDL_GetTicks();
		
		if ((SDL_GetTicks() - elapsedTime) >= 1000) {
			printf_s("%i\n", cycles);
			elapsedTime = SDL_GetTicks();

			cycles = 0;
		}

		cycles += 1;

		shaderProgram->use();

		while (SDL_PollEvent(&event)) {
			eventHandle(event);
		}

		timeValue = SDL_GetTicks();
		greenValue = ((sin(timeValue * 180 / M_PI) / 2) + 0.5);
		redValue = ((sin(timeValue * 180 / M_PI + 25) / 2) + 0.5);

		rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians((float)(rotate % 360)), glm::vec3(0.0f, 1.0f, 0.0f));
		rotate++;
		transformMat = translateMat * rotateMat * scalingMatrix; //translation rotation scal

		draw(window);

		currTime = SDL_GetTicks();

		GLfloat delay = ((1 / FPS) * 1000 - (currTime - prevTime));

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
	glUniform1f(vertexColorLocation, timeValue);
	glUniformMatrix4fv(transformLocation, 1, false, &transformMat[0][0]);
	glUniformMatrix4fv(projLocation, 1, false, &projMat[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, out_vertices.size());
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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