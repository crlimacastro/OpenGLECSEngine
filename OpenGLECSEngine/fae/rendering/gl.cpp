#include "gl.h"

using namespace fae;

fae::GLElementBufferObject::GLElementBufferObject(const std::vector<GLuint>& data)
	: GLBufferObject(), data(data)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
	Unbind();
}

fae::GLElementBufferObject::~GLElementBufferObject()
{
	GLint id;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);
	if (id == this->id) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLBufferObject& fae::GLElementBufferObject::Unbind()
{
	GLint id;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);
	if (id != this->id) return *this;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return *this;
}

fae::GLVertexArrayObject::GLVertexArrayObject()
{
	glCreateVertexArrays(1, &id);
}

fae::GLVertexArrayObject::~GLVertexArrayObject()
{
	GLint id;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
	if (id != 0 && id == this->id) glBindVertexArray(0);
	if (id != 0) glDeleteVertexArrays(1, &this->id);
}

IBindable& fae::GLVertexArrayObject::Bind()
{
	glBindVertexArray(id);
	return *this;
}

IBindable& fae::GLVertexArrayObject::Unbind()
{
	GLint id;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
	if (id != this->id) return *this;
	glBindVertexArray(0);
	return *this;
}


fae::GLVertexBufferObject::GLVertexBufferObject(const std::vector<Vertex>& data)
	: GLBufferObject(), data(data)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
	Unbind();
}

fae::GLVertexBufferObject::~GLVertexBufferObject()
{
	GLint id;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
	if (id == this->id) Unbind();
}

GLBufferObject& fae::GLVertexBufferObject::Unbind()
{
	GLint id;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
	if (id != this->id) return *this;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return *this;
}