#pragma once

#include "buffers/buffers.h"
#include "../math/math.h"

namespace sam_engine { namespace graphics {

	struct Vertex {

		math::vec3 position;
		math::vec4 color;

	};

	class Mesh {

	private:
		VertexArray* m_VAO;
		IndexBuffer* m_IBO;

	public:
		Mesh(VertexArray* vao, IndexBuffer* ibo);
		~Mesh();

		void render();
		static Mesh* createCube(float size);

	};

} }