#include "GLVertexArrayObject.h"

using namespace fae;

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