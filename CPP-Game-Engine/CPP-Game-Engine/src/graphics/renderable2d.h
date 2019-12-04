#pragma once

#include "../math/math.h"
#include "buffers/buffers.h"
#include "shader.h"

namespace sam_engine { namespace graphics {

	class Renderable2D{

	protected:
		math::vec3 m_Position;
		math::vec2 m_Size;
		math::vec4 m_Color;

		VertexArray* m_VAO;
		IndexBuffer* m_IBO;

		Shader &m_Shader;

	public:
		Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color, Shader shader)
			:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader) {
		
			m_VAO = new VertexArray();
			GLfloat vertices[] = {
				0, 0, 0,
				0, size.y, 0,
				size.x, size.y, 0,
				size.x, 0, 0
			};

			GLfloat colors[] = {
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_VAO->bindBuffer(new VertexBuffer(vertices, 4 * 3, 3), 0);
			m_VAO->bindBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_IBO = new IndexBuffer(indices, 6);
		
		}

		virtual ~Renderable2D() {
		
			delete m_VAO;
			delete m_IBO;
		
		}

		inline const VertexArray* getVAO() const { return m_VAO; }
		inline const IndexBuffer* getIBO() const { return m_IBO; }

		inline Shader& getShader() const { return m_Shader; }

		inline const math::vec3& getPosition() const { return m_Position; }
		inline const math::vec2& getSize() const { return m_Size; }
		inline const math::vec4& getColor() const { return m_Color; }

	};

} }