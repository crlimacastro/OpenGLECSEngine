#include "GLBufferObject.h"

fae::GLBufferObject::GLBufferObject()
{
	glGenBuffers(1, &id);
}

fae::GLBufferObject::~GLBufferObject()
{
	if (id != 0) glDeleteBuffers(1, &id);
}
