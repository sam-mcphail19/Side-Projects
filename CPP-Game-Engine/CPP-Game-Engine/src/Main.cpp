
#include "../src/utils/timer.h"
#include "io/Window.h"
#include "math/math.h"
#include "graphics/shader.h"
#include "graphics/buffers/buffers.h"
#include "graphics/batchRenderer2d.h"
#include "graphics/simpleRenderer2d.h"
#include "graphics/sprite.h"

#include <time.h>

#define WIDTH 1600
#define HEIGHT 900

int main() {

	using namespace sam_engine;
	using namespace io;
	using namespace math;
	using namespace graphics;

	Window window("Game Engine", WIDTH, HEIGHT);

	std::cout  << glGetString(GL_VERSION) << std::endl;
	
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();

	std::vector<Renderable2D*> sprites;

	srand((unsigned int)time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05f) {

		for (float x = 0; x < 16.0f; x += 0.05f) {

			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
		
		}

	}
	
	shader.setUniformMat4("proj_matrix", mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	BatchRenderer2D renderer;

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed()) {

		double x, y;
		window.getInput().getMousePos(x, y);
		//vec2 mouse_pos(x, y);
		vec2 mouse_pos((float)(x*16.0f/WIDTH), (float)(9.0f - y*9.0f/HEIGHT));

		shader.setUniform2f("light_pos", mouse_pos);

		window.clear();
		renderer.begin();
		
		for (int i = 0; i < sprites.size(); i++) {

			renderer.submit(sprites[i]);
		
		}

		renderer.end();
		renderer.flush();
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

