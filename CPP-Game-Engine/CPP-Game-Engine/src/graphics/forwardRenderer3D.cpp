
#include "forwardRenderer3D.h"

namespace sam_engine { namespace graphics {

	ForwardRenderer3D::ForwardRenderer3D() {
	
	

	}

	void ForwardRenderer3D::init() {



	}

	void ForwardRenderer3D::begin() {

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		m_Buffer.clear();

	}

	void ForwardRenderer3D::submit(Mesh *mesh) {

		m_Buffer.push_back(mesh);

	}

	void ForwardRenderer3D::end() {



	}

	void ForwardRenderer3D::flush() {

		while (!m_Buffer.empty()) {

			m_Buffer.front()->render();
			m_Buffer.pop_front();

		}

	}

}}