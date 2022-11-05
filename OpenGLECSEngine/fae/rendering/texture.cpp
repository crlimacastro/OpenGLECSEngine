#include "texture.h"
#include <SOIL2/SOIL2.h>

using namespace fae;

fae::Texture::Texture(std::string_view path)
{
	int width, height;
	this->data = std::shared_ptr <uint8_t[]>(SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGBA));
	this->width = width;
	this->height = height;
}

Texture& fae::Texture::Bind(int textureUnit)
{
	return *this;
}

fae::Texture::operator uint32_t() const
{
	return 0;
}

IBindable& fae::Texture::Bind()
{
	return *this;
}

IBindable& fae::Texture::Unbind()
{
	return *this;
}
