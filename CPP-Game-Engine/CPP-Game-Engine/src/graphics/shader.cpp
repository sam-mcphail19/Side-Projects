
#include "shader.h"


namespace sam_engine { namespace graphics {

	Shader::Shader(const char* vertPath, const char* fragPath) {
	
		m_VertPath = vertPath;
		m_FragPath = fragPath;
		m_ShaderID = load();
	
	}

	Shader::~Shader() {

		glDeleteProgram(m_ShaderID);

	}

	GLuint Shader::load() {

		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		
		std::string vertSourceString = read_file(m_VertPath);
		std::string fragSourceString = read_file(m_FragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();
		
		compileShader(vertSource, vertex);
		compileShader(fragSource, fragment);
		
		if (!vertex || !fragment) {
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	
	}

	GLuint Shader::compileShader(const char* source, GLuint &shader) {

		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
	
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_FALSE) {

			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shader, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(shader);
			return 0;

		}

		return shader;
	
	}

	void Shader::enable() const {

		glUseProgram(m_ShaderID);

	}

	void Shader::disable() const {

		glUseProgram(0);

	}

	GLint Shader::getUniformLocation(const GLchar* name) {
	
		return glGetUniformLocation(m_ShaderID, name);
	
	}

	void Shader::setUniform1f(const GLchar* name, float value) {

		glUniform1f(getUniformLocation(name), value);

	}

	void Shader::setUniform1i(const GLchar* name, int value) {

		glUniform1i(getUniformLocation(name), value);

	}

	void Shader::setUniform2f(const GLchar* name, const math::vec2& vector) {

		glUniform2f(getUniformLocation(name), vector.x, vector.y);

	}

	void Shader::setUniform3f(const GLchar* name, const math::vec3& vector) {

		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);

	}

	void Shader::setUniform4f(const GLchar* name, const math::vec4& vector) {

		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);

	}

	void Shader::setUniformMat4(const GLchar* name, const math::mat4& matrix) {

		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);

	}

}}