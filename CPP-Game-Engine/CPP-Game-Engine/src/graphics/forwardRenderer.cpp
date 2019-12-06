
#include "forwardRenderer.h"

namespace sam_engine { namespace graphics {

	ForwardRenderer::ForwardRenderer() {
	
	

	}

	void ForwardRenderer::init() {



	}

	void ForwardRenderer::begin() {

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		m_Buffer.clear();

	}

	void ForwardRenderer::submit(Mesh *mesh) {

		m_Buffer.push_back(mesh);

	}

	void ForwardRenderer::end() {



	}

	void ForwardRenderer::flush() {

		while (!m_Buffer.empty()) {
		
			m_Buffer.front()->render();
			m_Buffer.pop_front();

		}

	}

}}