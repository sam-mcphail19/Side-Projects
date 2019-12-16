

#include "batchRenderer3D.h"

namespace sam_engine { namespace graphics {

	BatchRenderer3D::BatchRenderer3D() {

		init();

	}

	BatchRenderer3D::~BatchRenderer3D() {
	
		glDeleteBuffers(1, &m_VBO);
	
	}

	void BatchRenderer3D::init() {

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_ATTR);
		glEnableVertexAttribArray(SHADER_COLOR_ATTR);

		glVertexAttribPointer(SHADER_VERTEX_ATTR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
		glVertexAttribPointer(SHADER_COLOR_ATTR, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, Vertex::color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		m_IndexCount = 0;

	}

	void BatchRenderer3D::begin() {

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (Vertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	}

	void BatchRenderer3D::submit(Mesh* mesh) {

		const Vertex* vertices = mesh->getVertices();
		const GLuint* indices = mesh->getIndices();

		for (int i = 0; i < mesh->getVerticesSize(); i++) {
		
			m_Buffer->position = vertices[i].position;
			m_Buffer->color = vertices[i].color;
			m_Buffer++;
		
		}

		for (int i = 0; i < mesh->getIndicesSize(); i++) {
		
			m_Indices[m_IndexCount + i] = (GLuint)indices[i];
		
		}

		m_IndexCount += mesh->getIndicesSize();

	}

	void BatchRenderer3D::end() {

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void BatchRenderer3D::flush() {

		m_IBO = new IndexBuffer(m_Indices, m_IndexCount);

		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
		delete m_IBO;

	}

} }