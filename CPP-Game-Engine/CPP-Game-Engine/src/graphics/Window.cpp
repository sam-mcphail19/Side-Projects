#include "Window.h"

namespace sam_engine { namespace graphics {

	Window::Window(const char* name, int width, int height) {
		m_Name = name;
		m_Width = width;
		m_Height = height;
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

		return true;
		
	}

	void Window::clear() const {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
	void Window::update() {

		glfwSwapBuffers(m_Window);
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);
		glfwPollEvents();

	}

	bool Window::closed() {
		return glfwWindowShouldClose(m_Window);
	}

}}
