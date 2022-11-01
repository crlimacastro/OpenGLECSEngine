#include "Texture.h"
#include <SOIL2/SOIL2.h>

fae::Texture::Texture(std::string_view path)
{
	int width, height;
	this->data = std::shared_ptr <uint8_t[]>(SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGBA));
	this->width = width;
	this->height = height;
}