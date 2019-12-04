#pragma once
#include <glew.h>
#include <vector>

#include "vertexBuffer.h"


namespace sam_engine { namespace graphics {

	class VertexArray {

	private:
		GLuint m_ArrayID;
		std::vector<VertexBuffer*> m_Buffers;

	public:
		VertexArray();
		~VertexArray();

		void bindBuffer(VertexBuffer *buffer, int index);

		void bind() const;
		void unbind() const;

	};

} }