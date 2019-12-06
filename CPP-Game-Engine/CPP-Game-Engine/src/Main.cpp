
#include "../src/utils/timer.h"
#include "io/Window.h"
#include "math/math.h"
#include "graphics/buffers/buffers.h"
#include "graphics/shader.h"
#include "graphics/buffers/buffers.h"
#include "graphics/batchRenderer2d.h"
#include "graphics/sprite.h"
#include "graphics/forwardRenderer3D.h"
#include "graphics/batchRenderer3D.h"
#include "graphics/mesh.h"

#include <time.h>

#define WIDTH 1600
#define HEIGHT 900

int main() {

	using namespace sam_engine;
	using namespace io;
	using namespace math;
	using namespace graphics;

	Window window("Game Engine", WIDTH, HEIGHT);

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();
	
	//shader.setUniformMat4("proj_matrix", mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	shader.setUniformMat4("proj_matrix", mat4::perspective(90, 16.0f/9.0f, 0.1f, 100.0f));

	ForwardRenderer3D renderer;

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	std::vector<Mesh*> cubes;

	for (int i = -9; i < 10; i++) {
		
		for (int j = -9; j < 10; j++) {
		
			cubes.push_back(Mesh::createCube2(2.0f, vec3(i * 2.0f, j * 2.0f, -25)));
		
		}
	
	}

	float angle = 0;

	while (!window.closed()) {

		window.clear();

		mat4 mat = mat4::translate(vec3(0,0, 25));
		mat *= mat4::rotate(angle, vec3(0, 1, 0));
		mat *= mat4::rotate(angle, vec3(1, 0, 0));
		mat *= mat4::translate(vec3(0, 0, -25));

		shader.setUniformMat4("model_matrix", mat);

		renderer.begin();

		for (int i = 0; i < cubes.size(); i++) {
		
			renderer.submit(cubes[i]);
		
		}

		renderer.end();
		renderer.flush();

		window.update();

		angle += 0.05f;

		frames++;
		if (time.elapsed() - timer > 1.0f) {

			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		
		}

	}
	
	return 0;
	
}

