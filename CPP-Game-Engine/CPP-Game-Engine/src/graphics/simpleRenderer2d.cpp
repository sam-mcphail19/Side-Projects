
#include "simpleRenderer2d.h"

namespace sam_engine { namespace graphics {

	void SimpleRenderer2D::submit(const Renderable2D *renderable) {
	
		m_Queue.push_back(renderable);

	}

	void SimpleRenderer2D::flush() {
	
		while (!m_Queue.empty()) {
		
			const Renderable2D* renderable = m_Queue.front();
			renderable->getVAO()->bind();
			renderable->getIBO()->bind();

			renderable->getShader().setUniformMat4("model_matrix", math::mat4::translate(renderable->getPosition()));
			glDrawElements(GL_TRIANGLES, renderable->getIBO()->getSize(), GL_UNSIGNED_SHORT, nullptr);

			renderable->getIBO()->unbind();
			renderable->getVAO()->unbind();

			m_Queue.pop_front();
		
		}
	
	}

}}