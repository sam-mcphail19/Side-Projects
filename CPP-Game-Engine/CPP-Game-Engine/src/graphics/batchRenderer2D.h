#pragma once

#include "buffers/buffers.h"
#include "renderable2d.h"
#include "renderer2d.h"

#include <cstddef>

namespace sam_engine { namespace graphics {

#define SHADER_VERTEX_ATTR 0
#define SHADER_COLOR_ATTR 1

#define MAX_SPRITES 60000
#define MAX_INDICES 360000 // MAX_SPRITES * 6 indices to draw 2 triangles
#define SPRITE_SIZE sizeof(VertexData) * 4 //each sprite has 4 vertices

	class BatchRenderer2D : public Renderer2D {

	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		VertexData* m_Buffer;

	private:
		void init();

	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin();
		void submit(const Renderable2D* renderable) override;
		void end();
		void flush() override;

	};

} }
