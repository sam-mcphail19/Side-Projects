#pragma once
#include <glew.h>

namespace sam_engine { namespace graphics {

	class IndexBuffer {

	private:
		GLuint m_BufferID;
		GLuint m_Size;

	public:
		IndexBuffer(GLushort *data, GLuint size);
		IndexBuffer(GLuint *data, GLuint size);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		GLuint getSize() const;

	};

} }