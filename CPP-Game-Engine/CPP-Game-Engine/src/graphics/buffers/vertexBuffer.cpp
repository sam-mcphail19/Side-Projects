
#include "vertexBuffer.h"

namespace sam_engine { namespace graphics {

	VertexBuffer::VertexBuffer(GLfloat* data, GLuint size, GLuint count) {
	
		m_Count = count;

		glGenBuffers(1, &m_BufferID);
		bind();
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
		unbind();
	
	}

	VertexBuffer::~VertexBuffer() {
	
		glDeleteBuffers(1, &m_BufferID);
	
	}

	void VertexBuffer::bind() const {
	
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	
	}

	void VertexBuffer::unbind() const {

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	GLuint VertexBuffer::getCount() const {
	
		return m_Count;

	}

} }