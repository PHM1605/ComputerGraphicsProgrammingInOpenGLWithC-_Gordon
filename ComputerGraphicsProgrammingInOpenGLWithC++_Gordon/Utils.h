#pragma once
#include <GL/glew.h>

class Utils {
public:
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static bool checkOpenGLError();
	static std::string readShaderSource(const char* filePath);
	static GLuint createShaderProgram(const char* vp, const char* fp);
};