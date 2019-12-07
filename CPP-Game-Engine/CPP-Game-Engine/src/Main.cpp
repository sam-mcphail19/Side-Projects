
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
#include "graphics/camera.h"

#include <time.h>

#define WIDTH 1600
#define HEIGHT 900

using namespace sam_engine;
using namespace io;
using namespace math;
using namespace graphics;

Window window("Game Engine", WIDTH, HEIGHT);

Camera camera = Camera(vec3(0, 0, -5), 0.0f, 0.0f);

double lastMouseX = 0, lastMouseY = 0;
float lastTime = glfwGetTime();

void input();

int main() {

	window.setBackground(0.2f, 0.2f, 0.2f);

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();
	
	//mat4 projMat = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	mat4 projMat = mat4::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	ForwardRenderer3D renderer;

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	std::vector<Mesh*> cubes;

	for (int i = -5; i < 6; i++) {
		
		for (int j = -5; j < 6; j++) {
		
			//cubes.push_back(Mesh::createCube2(2.0f, vec3(i * 3.0f, j * 3.0f, 0)));
		
		}
	
	}

	cubes.push_back(Mesh::createCube2(1.0f, vec3(0, 0, 0)));
	float angle = 0;

	while (!window.closed()) {

		window.clear();
		
		input();

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


void input() {

	Input input = window.getInput();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	lastTime = glfwGetTime();

	float speed = 10 * deltaTime;
	vec3 cameraPos = camera.getPos();

	if(input.isKeyPressed(GLFW_KEY_W)) {
		
		camera.setPos(vec3(cameraPos.x, cameraPos.y, cameraPos.z + speed));

	}
	if (input.isKeyPressed(GLFW_KEY_A)) {

		camera.setPos(vec3(cameraPos.x - speed, cameraPos.y, cameraPos.z));

	} 
	if (input.isKeyPressed(GLFW_KEY_S)) {

		camera.setPos(vec3(cameraPos.x, cameraPos.y, cameraPos.z - speed));

	} 
	if (input.isKeyPressed(GLFW_KEY_D)) {

		camera.setPos(vec3(cameraPos.x + speed, cameraPos.y, cameraPos.z));

	}
	if (input.isKeyPressed(GLFW_KEY_SPACE)) {

		camera.setPos(vec3(cameraPos.x, cameraPos.y + speed, cameraPos.z));

	}
	if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {

		camera.setPos(vec3(cameraPos.x, cameraPos.y - speed, cameraPos.z));

	}

	if (input.isButtonPressed(GLFW_MOUSE_BUTTON_1)) {
		 
		glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	}
	else {
	
		glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	
	}

}
