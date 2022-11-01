#include "GLShaderProgram.h"

#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace fae;

fae::GLShaderProgram::GLShaderProgram()
{
	id = glCreateProgram();
}

fae::GLShaderProgram::~GLShaderProgram()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (id != 0 && id == this->id) glUseProgram(0);

	if (id != 0) glDeleteProgram(id);
	if (vertexShader != 0) glDeleteShader(vertexShader);
	if (fragmentShader != 0) glDeleteShader(fragmentShader);
	if (geometryShader != 0) glDeleteShader(geometryShader);
}

fae::GLShaderProgram::operator uint32_t() const
{
	return id;
}

IBindable& fae::GLShaderProgram::Bind()
{
	glUseProgram(id);
	return *this;
}

IBindable& fae::GLShaderProgram::Unbind()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (id != this->id) return *this;
	glUseProgram(0);
	return *this;
}

GLuint LoadShaderFromSource(const GLchar* source, GLenum shaderType)
{
	// match shader version to GL version
	std::string srcStr = source;
	GLint majorVersion, minorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	srcStr = srcStr.replace(srcStr.find("#version"), 12, "#version " + std::to_string(majorVersion) + std::to_string(minorVersion) + "0");
	const char* src = srcStr.c_str();

	// create shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, 0);
	glCompileShader(shader);

	// check for errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		cout << "Error compiling " << shaderType << endl << shader << endl << infoLog << endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

IShaderProgram& fae::GLShaderProgram::LoadVertexFromSource(const char* source)
{
	vertexShader = LoadShaderFromSource(source, GL_VERTEX_SHADER);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::LoadFragmentFromSource(const char* source)
{
	fragmentShader = LoadShaderFromSource(source, GL_FRAGMENT_SHADER);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::LoadGeometryFromSource(const char* source)
{
	geometryShader = LoadShaderFromSource(source, GL_GEOMETRY_SHADER);
	return *this;
}

GLuint LoadShaderFromFile(const char* path, GLenum shaderType)
{
	// open file stream
	ifstream input;
	input.open(path);

	// check that file opened correctly
	if (!input.is_open())
	{
		cout << "Error reading shader file at " << path << endl;
		input.close();
		return 0;
	}

	// read shader line by line
	std::string source = "";
	std::string line = "";
	while (getline(input, line))
	{
		source += line + "\n";
	}
	input.close();

	return LoadShaderFromSource(source.c_str(), shaderType);
}

IShaderProgram& fae::GLShaderProgram::LoadVertexFromFile(const char* path)
{
	vertexShader = LoadShaderFromFile(path, GL_VERTEX_SHADER);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::LoadFragmentFromFile(const char* path)
{
	fragmentShader = LoadShaderFromFile(path, GL_FRAGMENT_SHADER);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::LoadGeometryFromFile(const char* path)
{
	geometryShader = LoadShaderFromFile(path, GL_GEOMETRY_SHADER);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::Link()
{
	// attach shaders & link program
	if (vertexShader != 0) glAttachShader(id, vertexShader);
	if (fragmentShader != 0) glAttachShader(id, fragmentShader);
	if (geometryShader != 0) glAttachShader(id, geometryShader);
	glLinkProgram(id);

	// check for errors
	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(id, 512, 0, infoLog);
		cout << "Error linking shader program " << id << endl << infoLog << endl;
	}

	// cleanup
	if (vertexShader != 0)
	{
		glDeleteShader(vertexShader);
		vertexShader = 0;
	}
	if (fragmentShader != 0)
	{
		glDeleteShader(fragmentShader);
		fragmentShader = 0;
	}
	if (geometryShader != 0)
	{
		glDeleteShader(geometryShader);
		geometryShader = 0;
	}

	return *this;
}

IShaderProgram& fae::GLShaderProgram::set1i(const char* name, int value)
{
	Bind();
	glUniform1i(glGetUniformLocation(id, name), value);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::set1f(const char* name, float value)
{
	Bind();
	glUniform1f(glGetUniformLocation(id, name), value);
	return *this;
}

IShaderProgram& fae::GLShaderProgram::setv2f(const char* name, glm::fvec2 value)
{
	Bind();
	glUniform2fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	return *this;
}

IShaderProgram& fae::GLShaderProgram::setv3f(const char* name, glm::fvec3 value)
{
	Bind();
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	return *this;
}

IShaderProgram& fae::GLShaderProgram::setm3f(const char* name, glm::fmat3 value, bool transpose)
{
	Bind();
	glUniformMatrix3fv(glGetUniformLocation(id, name), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	return *this;
}

IShaderProgram& fae::GLShaderProgram::setm4f(const char* name, glm::fmat4 value, bool transpose)
{
	Bind();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	return *this;
}
