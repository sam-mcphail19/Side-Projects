#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Input.h"

namespace sam_engine { namespace io {

	class Window {

	private:
		const char* m_Name;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		Input m_Input;

	public:
		Window(const char* name, int width, int height);
		~Window();
		void center();
		void clear() const;
		void update();
		bool closed();
		void setBackground(float r, float g, float b);
		int getWidth() const { return m_Width; };
		int getHeight() const { return m_Height; };
		Input getInput() const { return m_Input; };

	private:
		bool init();
	};

}}