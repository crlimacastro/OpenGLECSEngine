#include "RendererPlugin.h"
#include <fstream>
#include <format>
#include <iostream>
#include <GL/glew.h>
#include <entt/entt.hpp>
#include <SOIL2/SOIL2.h>
#include "Vertex.h"
#include "WindowPlugin.h"

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
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (id == this->id)
	{
		Unbind();
	}
	glDeleteProgram(id);
}

GLO& gfe::Shader::Bind()
{
	glUseProgram(id);
	return *this;
}

GLO& gfe::Shader::Unbind()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (id != this->id)
	{
		return *this;
	}
	glUseProgram(0);
	return *this;
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

std::vector<Vertex> vertices{
		{ glm::vec3{ -0.5f, 0.5, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec2{ 0, 1 } },
		{ glm::vec3{ -0.5, -0.5 , 0 }, glm::vec3{ 0, 1, 0 }, glm::vec2{ 0, 0 } },
		{ glm::vec3{ 0.5, -0.5, 0 }, glm::vec3{ 0, 0, 1 }, glm::vec2{ 1, 0 } },
		{ glm::vec3{ 0.5f, 0.5, 0 }, glm::vec3{ 1, 1, 0 }, glm::vec2{ 1, 1 } },
};

std::vector<GLuint> indices{
	0, 1, 2,
	0, 2, 3,
};

GLuint texture0;
Shader* coreShader;
VAO* vao;

void SetupRenderer(const void*, entt::registry& registry)
{
	// init glew
	glewExperimental = GL_TRUE;
	glewInit();

	// setup gl settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	coreShader = new Shader("vertex_core.glsl", "fragment_core.glsl");
	vao = new VAO();
	vao->Bind();
	VBO vbo{ vertices };
	vbo.Bind();
	EBO ebo{ indices };
	ebo.Bind();

	// enable attributes
	GLuint attribLoc = 0;

	// position
	attribLoc = glGetAttribLocation(*coreShader, "vertex_position");
	glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(attribLoc);

	// color
	attribLoc = glGetAttribLocation(*coreShader, "vertex_color");
	glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(attribLoc);

	// texcoord
	attribLoc = glGetAttribLocation(*coreShader, "vertex_texcoord");
	glVertexAttribPointer(attribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(attribLoc);

	// drawing texture
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int texWidth = 0;
	int texHeight = 0;
	unsigned char* image = SOIL_load_image("brick.jpg", &texWidth, &texHeight, NULL, SOIL_LOAD_RGBA);
	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
	}

	vao->Unbind();

	registry.ctx().emplace<Renderer>(*coreShader, *vao);
}

void UpdateRenderer(const void*, entt::registry& registry)
{
	// clear
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Set current shader & VAO
	auto& renderer = registry.ctx().at<Renderer>();
	renderer.currentShader.Bind();
	renderer.currentVAO.Bind();

	// update uniforms
	glUniform1i(glGetUniformLocation(renderer.currentShader, "texture0"), 0);

	// activate texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	// draw
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// Swap buffers
	auto& window = registry.ctx().at<Window>();
	glfwSwapBuffers(window);
	glFlush();

	// Unbinc shader & VAO
	renderer.currentShader.Unbind();
	renderer.currentVAO.Unbind();

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CleanRenderer(const void*, entt::registry& registry)
{
	delete coreShader;
	delete vao;
	glDeleteTextures(1, &texture0);
}

void gfe::RendererPlugin(App& app)
{
	app.AddStartSystem(SetupRenderer)
		.AddUpdateSystem(UpdateRenderer)
		.AddStopSystem(CleanRenderer);
}
