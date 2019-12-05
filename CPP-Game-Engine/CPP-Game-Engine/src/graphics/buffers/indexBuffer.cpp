
#include "indexBuffer.h"

namespace sam_engine { namespace graphics {

	IndexBuffer::IndexBuffer(GLushort* data, GLuint size) {

		m_Size = size;

		glGenBuffers(1, &m_BufferID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), data, GL_STATIC_DRAW);
		unbind();
	
	}

	IndexBuffer::IndexBuffer(GLuint* data, GLuint size) {

		m_Size = size;

		glGenBuffers(1, &m_BufferID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
		unbind();

	}

	IndexBuffer::~IndexBuffer() {
	
		glDeleteBuffers(1, &m_BufferID);
	
	}

	void IndexBuffer::bind() const {
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	
	}

	void IndexBuffer::unbind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	GLuint IndexBuffer::getSize() const {
	
		return m_Size;
	
	}

} }