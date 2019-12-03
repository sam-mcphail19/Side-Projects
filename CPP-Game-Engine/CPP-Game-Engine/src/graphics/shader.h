#pragma once

#include <vector>
#include <glew.h>
#include <iostream>

#include "../utils/fileutils.h"
#include "../math/math.h"

namespace sam_engine { namespace graphics {

	class Shader {

	private:
		const char *m_VertPath;
		const char *m_FragPath;
		GLuint m_ShaderID;

	private:
		GLuint load();
		GLuint compileShader(const char* source, GLuint &shader);

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		void disable() const;

		GLint getUniformLocation(const GLchar* name);

		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const math::vec2& vector);
		void setUniform3f(const GLchar* name, const math::vec3& vector);
		void setUniform4f(const GLchar* name, const math::vec4& vector);
		void setUniformMat4(const GLchar* name, const math::mat4& matrix);

	};

} }