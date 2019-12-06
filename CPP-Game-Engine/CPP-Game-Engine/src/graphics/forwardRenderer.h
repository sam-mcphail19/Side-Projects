#pragma once

#include "renderer3D.h"

namespace sam_engine { namespace graphics {

	class ForwardRenderer : public Renderer3D {

	private:

	private:
		void init() override;

	public:
		ForwardRenderer();

		void begin() override;
		void submit(Mesh* mesh) override;
		void end() override;
		void flush() override;

	};

}}