#include "Window.h"

namespace sam_engine { namespace io {

	void window_resize(GLFWwindow* window, int width, int height);

	Window::Window(const char* name, int width, int height) {
		m_Name = name;
		m_Width = width;
		m_Height = height;
		m_Input = Input();
		if(!init())
			glfwTerminate();
	}

	Window::~Window() {
		
		glfwTerminate();

	}

	bool Window::init() {

		if (!glfwInit()) {
			std::cout << "Could not initialize GLFW" << std::endl;
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);

		if (!m_Window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, this->m_Input.key_callback);

		return true;
		
	}

	void Window::clear() const {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
	void Window::update() {

		glfwSwapBuffers(m_Window);
		glfwPollEvents();

	}

	bool Window::closed() {
		return glfwWindowShouldClose(m_Window);
	}

	void window_resize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

}}
