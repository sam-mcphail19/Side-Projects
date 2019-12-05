
#include "simpleRenderer2d.h"

namespace sam_engine { namespace graphics {

	void SimpleRenderer2D::submit(const Renderable2D *renderable) {
	
		m_Queue.push_back((Sprite*) renderable);

	}

	void SimpleRenderer2D::flush() {
	
		while (!m_Queue.empty()) {
		
			const Sprite *sprite = m_Queue.front();
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();

			Shader shader = sprite->getShader();
			shader.setUniformMat4("model_matrix", math::mat4::translate(sprite->getPosition()));
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getSize(), GL_UNSIGNED_SHORT, nullptr);

			sprite->getIBO()->unbind();
			sprite->getVAO()->unbind();

			m_Queue.pop_front();
		
		}
	
	}

}}