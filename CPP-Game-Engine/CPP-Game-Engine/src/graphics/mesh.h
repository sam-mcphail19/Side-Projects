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
		Vertex* m_Vertices;
		GLuint* m_Indices;
		int m_VerticesSize;
		int m_IndicesSize;

		VertexArray* m_VAO;
		IndexBuffer* m_IBO;

	public:
		Mesh(Vertex* vertices, GLuint* indices, int verticesSize, int indicesSize);
		Mesh(VertexArray* vao, IndexBuffer* ibo);
		~Mesh();

		void render();
		static Mesh* createCube(float size, math::vec3 position);
		static Mesh* createCube2(float size, math::vec3 position);

		inline Vertex* getVertices() const { return m_Vertices; };
		inline GLuint* getIndices() const { return m_Indices; };
		inline int getVerticesSize() const { return m_VerticesSize; };
		inline int getIndicesSize() const { return m_IndicesSize; };

	};

} }