#pragma once
#include <string_view>

#include "../texture.h"

namespace fae
{
	struct GLTexture : public GLObject, public Texture
	{
		GLTexture(std::string_view path);
		~GLTexture();
	};
}
