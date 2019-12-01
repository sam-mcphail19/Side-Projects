#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>

namespace sam_engine { namespace io {

	#define MAX_KEYS 1024
	#define MAX_BUTTONS 32

	class Input {

	private:
		static bool m_Keys[MAX_KEYS];
		static bool m_MouseButtons[MAX_BUTTONS];
		static double mouseX, mouseY;

	public:
		Input();
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};

}}