#pragma once
#include <string_view>
#include <memory>
#include <cstdint>

namespace fae
{
	class Texture
	{
	public:
		Texture(std::string_view path);

		std::shared_ptr<uint8_t[]> GetData() { return data; }
		size_t GetWidth() { return width; }
		size_t GetHeight() { return height; }
	protected:
		std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>({});
		size_t width = 0;
		size_t height = 0;

	};
}