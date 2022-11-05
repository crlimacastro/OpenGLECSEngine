#include "GLRenderer.h"

using namespace fae;

GLRenderer& fae::GLRenderer::Bind(const GLVertexArrayObject& vao)
{
	glBindVertexArray(vao.id);
	return *this;
}

GLRenderer& fae::GLRenderer::Bind(const GLVertexBufferObject& vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
	return *this;
}

GLRenderer& fae::GLRenderer::Bind(const GLElementBufferObject& ebo)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.id);
	return *this;
}

Renderer& fae::GLRenderer::Bind(const IShaderProgram& shaderProgram)
{
	glUseProgram(shaderProgram.GetId());
	return *this;
}

Renderer& fae::GLRenderer::Bind(const Texture& texture)
{
	// // O: insert return statement here
}

Renderer& fae::GLRenderer::Bind(const RendererBuffer& buffer)
{
	// // O: insert return statement here
}

Renderer& fae::GLRenderer::Clear()
{
	// // O: insert return statement here
}

Renderer& fae::GLRenderer::Begin()
{
	// // O: insert return statement here
}

Renderer& fae::GLRenderer::End()
{
	// // O: insert return statement here
}
