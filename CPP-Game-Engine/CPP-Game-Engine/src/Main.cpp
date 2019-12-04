
#include "graphics/shader.h"
#include "io/Window.h"
#include "math/math.h"
#include "graphics/buffers/buffers.h"
#include "graphics/simpleRenderer2d.h"
#include "graphics/renderable2d.h"

int main() {

	using namespace sam_engine;
	using namespace io;
	using namespace math;
	using namespace graphics;

	Window window("Game Engine", 1280, 720);

	std::cout << glGetString(GL_VERSION) << std::endl;	

	GLfloat vertices[] = {
#if 1	
		0.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 0.0f,
		5.0f, 3.0f, 0.0f,
		5.0f, 0.0f, 0.0f,
#else
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
#endif
	};

	GLushort indices[] = {

		0, 1, 2,
		2, 3, 0

	};
	
	/*
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);*/

	VertexArray vao;
	IndexBuffer ibo(indices, 6);

	vao.bindBuffer(new VertexBuffer(vertices, 4*3, 3), 0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();
	
	shader.setUniformMat4("proj_matrix", ortho);
	shader.setUniform4f("color", vec4(1.0f, 0.8f, 0.2f, 1.0f));

	SimpleRenderer2D renderer;
	Renderable2D box0(vec3(2, 2, 0), vec2(4, 2), vec4(1, 0, 0, 1), shader);
	Renderable2D box1(vec3(0.3f, 0.3f, 0), vec2(2, 5), vec4(1, 0, 1, 1), shader);
	Renderable2D box2(vec3(5, 5, 0), vec2(3, 3), vec4(1, 1, 0, 1), shader);
	Renderable2D box3(vec3(7, 8, 0), vec2(1, 3), vec4(0, 0, 1, 1), shader);
	
	while (!window.closed()) {

		double x, y;
		window.getInput().getMousePos(x, y);
		vec2 mouse_pos((float)(x*16.0f/1280.0f), (float)(9.0f - y*9.0f/720.0f));
		shader.setUniform2f("light_pos", mouse_pos);
	
		window.clear();
		renderer.submit(&box0);
		renderer.submit(&box1);
		renderer.submit(&box2);
		renderer.submit(&box3);
		renderer.flush();
		window.update();

		//angle += 0.1f;
	
	}
	
	return 0;
	
}

