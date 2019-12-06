#pragma once

#include "mesh.h"

#include <deque>

namespace sam_engine { namespace graphics {

	class Renderer3D {

	protected:
		std::deque<Mesh*> m_Buffer;
		 
	private:
		virtual void init() = 0;

	public:
		virtual void begin() = 0;
		virtual void submit(Mesh* mesh) = 0;
		virtual void end() = 0;
		virtual void flush() = 0;

	};

} }