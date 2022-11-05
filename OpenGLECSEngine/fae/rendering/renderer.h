#pragma once
#include <glm/glm.hpp>
#include "IShaderProgram.h"
#include "texture.h"

namespace fae
{
	struct RendererBuffer {

	};

	struct Renderer
	{
		glm::vec4 clearColor = { 1, 1, 1, 1 };

		virtual Renderer& Clear() = 0;
		virtual Renderer& Begin() = 0;
		virtual Renderer& End() = 0;

		virtual Renderer& Bind(const IShaderProgram& shaderProgram) = 0;
		virtual Renderer& Bind(const Texture& texture) = 0;
		virtual Renderer& Bind(const RendererBuffer& buffer) = 0;
	};
}