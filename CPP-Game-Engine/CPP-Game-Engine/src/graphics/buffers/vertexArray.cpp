
#include "vertexArray.h"

namespace sam_engine { namespace graphics {

	VertexArray::VertexArray() {

		glGenVertexArrays(1, &m_ArrayID);
	
	}

	VertexArray::~VertexArray() {
	
		for (int i = 0; i < m_Buffers.size(); i++)
			delete m_Buffers[i];

	}

	void VertexArray::bindBuffer(VertexBuffer *buffer, int index) {
	
		bind();
		buffer->bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getCount(), GL_FLOAT, GL_FALSE, 0, 0);

		unbind();
		buffer->unbind();
	
	}

	void VertexArray::bind() const {
	
		glBindVertexArray(m_ArrayID);
	
	}

	void VertexArray::unbind() const {

		glBindVertexArray(0);

	}

} }