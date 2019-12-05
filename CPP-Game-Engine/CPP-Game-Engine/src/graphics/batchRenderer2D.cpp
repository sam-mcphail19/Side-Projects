
#include "batchRenderer2D.h"

namespace sam_engine { namespace graphics {

	BatchRenderer2D::BatchRenderer2D() {
	
		init();

	}

	BatchRenderer2D::~BatchRenderer2D() {

		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);

	}

	void BatchRenderer2D::init() {

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, SPRITE_SIZE * MAX_SPRITES, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_ATTR);
		glEnableVertexAttribArray(SHADER_COLOR_ATTR);

		// vertex info starts at 0
		glVertexAttribPointer(SHADER_VERTEX_ATTR, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*) 0);
		glVertexAttribPointer(SHADER_COLOR_ATTR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (const GLvoid*) (offsetof(VertexData, VertexData::color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4; // get the next 4 vertices
		}

		m_IBO = new IndexBuffer(indices, INDICES_SIZE);

		glBindVertexArray(0);

	}

	void BatchRenderer2D::begin() {

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	}

	void BatchRenderer2D::submit(const Renderable2D* renderable) {

		if (sizeof(m_IndexCount) > MAX_INDICES)
			flush();

		const math::vec3& position = renderable->getPosition();
		const math::vec2& size = renderable->getSize();
		const math::vec4& color = renderable->getColor();

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		unsigned int c = a << 24 | b << 16 | g << 8 | r;

		m_Buffer->vertex = position;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = math::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = math::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = math::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->color = c;
		m_Buffer++;

		m_IndexCount += 6;

	}

	void BatchRenderer2D::end() {

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void BatchRenderer2D::flush() {

		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);
	
		m_IndexCount = 0;

	}

} }