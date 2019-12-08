
#include "../src/utils/timer.h"
#include "math/math.h"
#include "graphics/Window.h"
#include "graphics/buffers/buffers.h"
#include "graphics/shader.h"
#include "graphics/buffers/buffers.h"
#include "graphics/batchRenderer2d.h"
#include "graphics/sprite.h"
#include "graphics/forwardRenderer3D.h"
#include "graphics/batchRenderer3D.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"

#include <time.h>

#define WIDTH 1600
#define HEIGHT 900

using namespace sam_engine;
using namespace math;
using namespace graphics;

Window window("Game Engine", WIDTH, HEIGHT);

Camera camera = Camera(vec3(0, 0, -5), 0.0f, 0.0f);

int main() {

	window.setBackground(0.2f, 0.2f, 0.2f);

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();

	ForwardRenderer3D renderer;

	std::vector<Mesh*> cubes;

	for (int i = -5; i < 6; i++) {
		
		for (int j = -5; j < 6; j++) {
		
			cubes.push_back(Mesh::createCube2(2.0f, vec3(i * 3.0f, j * 3.0f, 0)));
		
		}
	
	}
	
	mat4 projMat = mat4::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float angle = 0;
	double lastMouseX = 0, lastMouseY = 0;
	double lastTime = glfwGetTime();

	while (!window.closed()) {

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = glfwGetTime();

		window.clear();
		
		float sensitivity = 15 * deltaTime;
		camera.input(&window, sensitivity, sensitivity);

		renderer.begin();
		for (int i = 0; i < cubes.size(); i++) {
		
			renderer.submit(cubes[i]);
		
		}
		renderer.end();
		renderer.flush();

		mat4 viewMat = *camera.createViewMatrix();
		
		mat4 modelMat = mat4::translate(vec3(0, 0, 2));
		//modelMat *= mat4::rotate(angle, vec3(0, 1, 0));
		//modelMat *= mat4::rotate(angle, vec3(1, 0, 0));

		shader.setUniformMat4("mvp", projMat * viewMat * modelMat);

		angle += 0.05f;

		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f) {

			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		
		}

	}
	
	return 0;
	
}
