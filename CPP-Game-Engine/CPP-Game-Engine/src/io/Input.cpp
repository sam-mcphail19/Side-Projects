#include "Input.h"

namespace sam_engine { namespace io {

	bool Input::m_Keys[MAX_KEYS];
	bool Input::m_MouseButtons[MAX_BUTTONS];
	double Input::mouseX;
	double Input::mouseY;

	Input::Input() {

		for(int i=0; i<MAX_KEYS; i++)
			m_Keys[i] = false;

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseButtons[i] = false;
	
	}

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

		m_Keys[key] = action != GLFW_RELEASE;
	
	}

	void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	
		m_MouseButtons[button] = action != GLFW_RELEASE;
	
	}

	void Input::cursor_pos_callback(GLFWwindow* window, double xPos, double yPos) {
	
		mouseX = xPos;
		mouseY = yPos;
	
	}

	bool Input::isKeyPressed(int keycode) {

		return m_Keys[keycode];

	}

	bool Input::isButtonPressed(int button) {

		return m_MouseButtons[button];

	}

	void Input::getMousePos(double& x, double& y) {
	
		x = mouseX;
		y = mouseY;

	}

}}