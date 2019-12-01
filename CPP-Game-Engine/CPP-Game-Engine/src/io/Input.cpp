#include "Input.h"

namespace sam_engine { namespace io {

	Input::Input() {
	

	
	}

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

		if (action == GLFW_PRESS) {
			//m_Keys[key] = true;
			std::cout << "Key: " << key << std::endl;
			std::cout << "Window: " << window << std::endl;
		}
		else if(action == GLFW_RELEASE){
			//m_Keys[key] = false;
		}
	
	}

}}