
#include <iostream>

#include "graphics\Window.h"

int main() {

	using namespace sam_engine;
	using namespace graphics;

	Window window("Game Engine", 1280, 720);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;
	

	while (!window.closed()) {
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}
	
	return 0;
	
}

