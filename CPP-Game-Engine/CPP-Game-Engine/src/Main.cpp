
#include "graphics/shader.h"
#include "io/Window.h"
#include "math/math.h"

int main() {

	using namespace sam_engine;
	using namespace io;
	using namespace math;
	using namespace graphics;

	Window window("Game Engine", 1280, 720);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;	

	GLfloat vertices[] = {
#if 0	
		3.0f, 3.0f, 0.0f,
		3.0f, 5.0f, 0.0f,
		5.0f, 5.0f, 0.0f,
		5.0f, 5.0f, 0.0f,
		5.0f, 3.0f, 0.0f,
		3.0f, 3.0f, 0.0f,
#else
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
#endif
	};
	
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();
	
	shader.setUniformMat4("proj_matrix", mat4::identity());
	shader.setUniformMat4("model_matrix", mat4::rotate(45, vec3(0, 0, 1)));

	shader.setUniform4f("color", vec4(1.0f, 0.8f, 0.2f, 1.0f));
	
	while (!window.closed()) {
	
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	
	}
	
	return 0;
	
}

