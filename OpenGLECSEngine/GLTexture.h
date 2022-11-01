#pragma once
#include <string_view>
#include "GLObject.h"
#include "Texture.h"

namespace fae
{
	struct GLTexture : public GLObject, public Texture
	{
		GLTexture(std::string_view path);
		~GLTexture();

		GLTexture& Bind(GLint textureUnit);

		// Inherited via GLObject
		GLObject& Bind();
		GLObject& Unbind();
	};
}
