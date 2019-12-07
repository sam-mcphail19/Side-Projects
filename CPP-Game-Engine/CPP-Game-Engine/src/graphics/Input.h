#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>

namespace sam_engine { namespace graphics {

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
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos);
		bool isKeyPressed(int keycode);
		bool isButtonPressed(int button);
		void getMousePos(double& x, double& y);
	};

}}