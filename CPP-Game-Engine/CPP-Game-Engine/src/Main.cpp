
#include <iostream>

#include "io/Window.h"
#include "math/math.h"
#include "utils/fileutils.h"

int main() {

	using namespace sam_engine;
	using namespace io;
	using namespace math;

	std::string file = read_file("src/Main.cpp");
	std::cout << file << std::endl;

	Window window("Game Engine", 1280, 720);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;	
	
	/*
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	*/

	return 0;
	
}

