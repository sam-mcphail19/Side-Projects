#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>

namespace sam_engine { namespace graphics {

	class Window {

	private:
		const char* m_Name;
		int m_Width, m_Height;
		GLFWwindow* m_Window;

	public:
		Window(const char* name, int width, int height);
		~Window();
		void update();
		void clear() const;
		bool closed();
		int getWidth() const { return m_Width; };
		int getHeight() const { return m_Height; };

	private:
		bool init();
	};

}}