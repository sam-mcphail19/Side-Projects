#pragma once

#include "renderer3D.h"

namespace sam_engine { namespace graphics {

#define SHADER_VERTEX_ATTR 0
#define SHADER_COLOR_ATTR 1

#define MAX_INDICES_3D 30000
#define MAX_BUFFER_SIZE sizeof(Vertex) * MAX_INDICES_3D

	class BatchRenderer3D : public Renderer3D{

	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;// add submitted mesh's indices at the current index
		Vertex* m_Buffer;
		GLuint* m_Indices = new GLuint[MAX_INDICES_3D];

	private:
		void init();

	public:
		BatchRenderer3D();
		~BatchRenderer3D();

		void begin();
		void submit(Mesh* mesh) override;
		void end();
		void flush() override;

	};

} }