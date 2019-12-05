#pragma once

#include "renderable2d.h"

namespace sam_engine { namespace graphics {

	class Sprite : public Renderable2D {
		
	private:
		VertexArray *m_VAO;
		IndexBuffer *m_IBO;

		Shader& m_Shader;

	public:
		Sprite(float x, float y, float width, float height, const math::vec4 color, Shader &shader);
		~Sprite();

		inline const VertexArray* getVAO() const { return m_VAO; };
		inline const IndexBuffer* getIBO() const { return m_IBO; };

		inline const Shader& getShader() const { return m_Shader; };

	};

} }