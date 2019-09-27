#include "window.h"

namespace sam_engine { namespace graphics {

	Window::Window(const char* name, int width, int height) {
		m_Name = name;
		m_Height = height;
		m_Width = width;
	}

} }