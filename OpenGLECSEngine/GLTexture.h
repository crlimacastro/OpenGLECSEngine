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

		virtual Texture& Bind(int textureUnit) override;

		// Inherited via GLObject
		virtual operator uint32_t() const override;
		virtual GLObject& Bind() override;
		virtual GLObject& Unbind() override;
	};
}
