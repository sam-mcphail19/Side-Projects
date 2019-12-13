#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Input.h"

namespace sam_engine { namespace graphics {

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
		void centerCursor();
		void centerCursorHorizontally(double y);
		void setCursorPos(double x, double y);
		void hideCursor();
		void showCursor();
		inline GLFWwindow* getWindow() const { return m_Window; };
		inline int getWidth() const { return m_Width; };
		inline int getHeight() const { return m_Height; };
		inline Input getInput() const { return m_Input; };

	private:
		bool init();
	};

}}