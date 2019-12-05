
#include "sprite.h"

namespace sam_engine { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, const math::vec4 color, Shader &shader)
		:Renderable2D(math::vec3(x,y,0), math::vec2(width, height), color), m_Shader(shader) {

		m_VAO = new VertexArray();
		GLfloat vertices[] = {
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0
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

	Sprite::~Sprite() {
	
		delete m_VAO;
		delete m_IBO;
	
	}

}}