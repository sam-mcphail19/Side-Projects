#include "Window.h"

namespace sam_engine { namespace graphics {

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
		
		if (glewInit() != GLEW_OK) {
			std::cout << "Could not initialize GLEW!" << std::endl;
			return false;
		}

		center();

		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, this->m_Input.key_callback);
		glfwSetMouseButtonCallback(m_Window, this->m_Input.mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, this->m_Input.cursor_pos_callback);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		return true;
		
	}

	void Window::center() {

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowPos(m_Window, (mode->width - m_Width) / 2, (mode->height - m_Height) / 2);
	
	}

	void Window::clear() const {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
	void Window::update() {

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;

		if (m_Input.isKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(m_Window, GL_TRUE);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();

	}

	bool Window::closed() {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::setBackground(float r, float g, float b) {
	
		glClearColor(r, g, b, 1.0f);
	
	}

	void Window::centerCursor() {

		setCursorPos(m_Width / 2, m_Height / 2);

	}

	void Window::centerCursorHorizontally(double y) {

		setCursorPos(m_Width / 2, y);

	}

	void Window::setCursorPos(double x, double y) {
	
		glfwSetCursorPos(m_Window, x, y);
		m_Input.cursor_pos_callback(m_Window, x, y);
	
	}

	void Window::hideCursor() {
	
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	}

	void Window::showCursor() {

		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}

	void window_resize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

}}
