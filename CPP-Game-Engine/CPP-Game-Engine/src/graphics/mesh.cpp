
#include "mesh.h"

namespace sam_engine { namespace graphics {

	Mesh::Mesh(VertexArray* vao, IndexBuffer* ibo)
	: m_VAO(vao), m_IBO(ibo) {
	

	
	}

	Mesh::~Mesh() {

		delete m_VAO;
		delete m_IBO;

	}

	void Mesh::render() {
	
		m_VAO->bind();
		m_IBO->bind();
		m_VAO->draw(m_IBO->getSize());
		m_IBO->unbind();
		m_VAO->unbind();
	
	}

	Mesh* Mesh::createCube(float size) {

		math::vec3 vertices[8];
		vertices[0] = math::vec3(-size / 2.0f, -size / 2.0f, size / 2.0f);
		vertices[1] = math::vec3(size / 2.0f, -size / 2.0f, size / 2.0f);
		vertices[2] = math::vec3(size / 2.0f, size / 2.0f, size / 2.0f);
		vertices[3] = math::vec3(-size / 2.0f, size / 2.0f, size / 2.0f);
		vertices[4] = math::vec3(-size / 2.0f, -size / 2.0f, -size / 2.0f);
		vertices[5] = math::vec3(size / 2.0f, -size / 2.0f, -size / 2.0f);
		vertices[6] = math::vec3(size / 2.0f, size / 2.0f, -size / 2.0f);
		vertices[7] = math::vec3(-size / 2.0f, size / 2.0f, -size / 2.0f);

		math::vec4 colors[8];
		colors[0] = math::vec4(0, 1, 1, 1);
		colors[1] = math::vec4(0, 0, 1, 1);
		colors[2] = math::vec4(1, 0, 1, 1);
		colors[3] = math::vec4(1, 1, 0, 1);
		colors[4] = math::vec4(0, 0, 1, 1);
		colors[5] = math::vec4(1, 0, 1, 1);
		colors[6] = math::vec4(0, 1, 0, 1);
		colors[7] = math::vec4(1, 0, 0, 1);

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			3, 2, 6, 6, 7, 3,
			7, 6, 5, 5, 4, 7,
			4, 0, 3, 3, 7, 4,
			0, 1, 5, 5, 4, 0,
			1, 5, 6, 6, 2, 1
		};

		VertexArray* vao = new VertexArray();

		vao->bindBuffer(new VertexBuffer((GLfloat*)vertices, (GLuint)8 * 3, (GLuint)3), 0);
		vao->bindBuffer(new VertexBuffer((GLfloat*)colors, (GLuint)8 * 4, (GLuint)4), 1);

		IndexBuffer* ibo = new IndexBuffer((GLuint*)indices, 36);

		return new Mesh(vao, ibo);
	
	}

} }