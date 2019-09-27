#pragma once

namespace sam_engine { namespace graphics {

	class Window {
	private:
		int m_Width, m_Height;
		const char* m_Name;
	public:
		Window(const char* name, int width, int height);
		~Window();
		void update() const;
	};

} }