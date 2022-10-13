#include "Shader.h"
#include <iostream>
#include <string>
#include <format>
#include <fstream>

using namespace gfe;

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
{
	// vertex shader
	GLuint vertexShader = CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);

	// fragment shader
	GLuint fragmentShader = CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);

	// shader program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// check for errors
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Error linking shader program from " << std::endl
			<< std::format("vertex shader file at '{0}'", vertexPath) << std::endl
			<< std::format("fragment shader file at '{0}'", fragmentPath) << std::endl
			<< infoLog << std::endl;
	}

	id = program;

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

GLuint Shader::CompileShaderFromFile(std::string_view path, GLenum shaderType)
{
	// open file stream
	std::ifstream inputStream;
	inputStream.open(path.data());

	// check that file opened correctly
	if (!inputStream.is_open())
	{
		std::cout << std::format("Error reading shader file at '{0}'", path) << std::endl;
		inputStream.close();
		return 0;
	}

	// read shader string line by line
	std::string content = "";
	std::string line = "";
	while (std::getline(inputStream, line))
	{
		content += line + "\n";
	}

	// clean up & return shader string
	inputStream.close();

	// create shader
	GLuint shader = glCreateShader(shaderType);
	const GLchar* src = content.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// check for errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << std::format("Error compiling shader from file at '{0}'", path) << std::endl
			<< infoLog << std::endl;
	}

	return shader;
}
