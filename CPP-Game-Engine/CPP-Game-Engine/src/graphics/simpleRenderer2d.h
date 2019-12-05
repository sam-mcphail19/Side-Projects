#pragma once

#include <deque>

#include "renderer2d.h"
#include "sprite.h"

namespace sam_engine { namespace graphics {

	class SimpleRenderer2D : public Renderer2D {

	private:
		std::deque<const Sprite*> m_Queue;
	
	public:
		void submit(const Renderable2D* renderable) override;
		void flush() override;

	};

} }