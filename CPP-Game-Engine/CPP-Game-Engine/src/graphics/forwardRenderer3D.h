#pragma once

#include "renderer3D.h"

namespace sam_engine { namespace graphics {

	class ForwardRenderer3D : public Renderer3D {

	private:
		std::deque<Mesh*> m_Buffer;

	private:
		void init() override;

	public:
		ForwardRenderer3D();

		void begin() override;
		void submit(Mesh* mesh) override;
		void end() override;
		void flush() override;

	};

}}