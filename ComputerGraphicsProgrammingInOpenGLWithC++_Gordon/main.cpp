#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define numVAOs 1

using namespace std;
using namespace glm;

GLuint renderingProgram;
GLuint vao[numVAOs];

mat4 buildTranslate(float x, float y, float z) {
	mat4 trans = mat4(
		1.0, 0.0, 0.0, 0.0, // first COLUMN, not row
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		x, y, z, 1.0);
	return trans;
}

mat4 buildRotateX(float rad) {
	mat4 xrot = mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, cos(rad), sin(rad), 0.0,
		0.0, -sin(rad), cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0
	);
	return xrot;
}

mat4 buildRotateY(float rad) {
	mat4 yrot = mat4(
		cos(rad), 0.0, -sin(rad), 0.0,
		0.0, 1.0, 0.0, 0.0,
		sin(rad), 0.0, cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0
	);
	return yrot;
}

mat4 buildRotateZ(float rad) {
	mat4 zrot = mat4(
		cos(rad), sin(rad), 0.0, 0.0,
		-sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
	return zrot;
}

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT); // clear the background to black, each time
	glUseProgram(renderingProgram);

	GLuint rotMatLoc = glGetUniformLocation(renderingProgram, "rotMat");
	mat4 rotMat= buildRotateZ(1.047); // rotate clockwise pi/3 rad
	glUniformMatrix4fv(rotMatLoc, 1, GL_FALSE, glm::value_ptr(rotMat));

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);
	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}