#pragma once
#include "../renderer.h"
#include "../gl.h"


namespace fae
{
	struct GLRenderer : public Renderer
	{
		GLRenderer& Bind(const GLVertexArrayObject& vao);
		GLRenderer& Bind(const GLVertexBufferObject& vbo);
		GLRenderer& Bind(const GLElementBufferObject& ebo);

		// Inherited via Renderer
		virtual Renderer& Clear() override;
		virtual Renderer& Begin() override;
		virtual Renderer& End() override;

		virtual Renderer& Bind(const IShaderProgram& shaderProgram) override;
		virtual Renderer& Bind(const Texture& texture) override;
		virtual Renderer& Bind(const RendererBuffer& buffer) override;
	};
}