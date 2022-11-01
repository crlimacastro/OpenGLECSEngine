#include "GLElementBufferObject.h"

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

GLBufferObject& fae::GLElementBufferObject::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	return *this;
}

GLBufferObject& fae::GLElementBufferObject::Unbind()
{
	GLint id;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);
	if (id != this->id) return *this;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return *this;
}
