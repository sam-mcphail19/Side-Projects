#pragma once
#include <glew.h>

namespace sam_engine { namespace graphics {

	class VertexBuffer {

	private:
		GLuint m_BufferID;
		GLuint m_Count; // size of thing to be rendered (vec2f vs vec4f)

	public:
		VertexBuffer(GLfloat *data, GLuint size, GLuint count);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		inline GLuint getCount() const { return m_Count; };
		inline GLuint getID() const { return m_BufferID; };

	};

} }