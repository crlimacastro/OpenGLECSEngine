#include "GLTexture.h"
#include <SOIL2/SOIL2.h>

using namespace fae;

fae::GLTexture::GLTexture(std::string_view path) : Texture(path)
{
	glGenTextures(1, &id);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
	glGenerateMipmap(GL_TEXTURE_2D);
	Unbind();
}

fae::GLTexture::~GLTexture()
{
	GLint id;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
	if (id == this->id) glBindTexture(GL_TEXTURE_2D, 0);
	if (id != 0) glDeleteTextures(1, &this->id);
}

GLTexture& fae::GLTexture::Bind(GLint textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
	return *this;
}

GLObject& fae::GLTexture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	return *this;
}

GLObject& fae::GLTexture::Unbind()
{
	glActiveTexture(0);
	GLint id;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
	if (id != this->id) return *this;
	glBindTexture(GL_TEXTURE_2D, 0);
	return *this;
}