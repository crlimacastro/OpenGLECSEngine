#include "GLVertexBufferObject.h"

using namespace fae;

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

GLBufferObject& fae::GLVertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	return *this;
}

GLBufferObject& fae::GLVertexBufferObject::Unbind()
{
	GLint id;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
	if (id != this->id) return *this;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return *this;
}
