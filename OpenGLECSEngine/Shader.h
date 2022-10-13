#pragma once
#include <string_view>
#include <GL/glew.h>

namespace gfe {
	struct Shader
	{
		GLuint id;

		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		~Shader();

		operator GLuint () { return id; }
		operator const GLuint() const { return id; }

	private:
		static GLuint CompileShaderFromFile(std::string_view path, GLenum shaderType);
	};
}