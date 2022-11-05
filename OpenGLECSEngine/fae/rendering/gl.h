#pragma once
#include <GL/glew.h>
#include <cstdint>
#include <vector>

#include "renderer.h"
#include "vertex.h"

#include "gl/GLRenderer.h"
#include "gl/GLShaderProgram.h"
#include "gl/GLTexture.h"

namespace fae
{
	struct GLObject
	{
		GLuint id = 0;
		operator uint32_t() const { return id; }
	};

	struct GLVertexArrayObject : public GLObject, public RendererBuffer
	{
		GLVertexArrayObject();
		~GLVertexArrayObject();
	};

	struct GLBufferObject : public GLObject
	{
		GLBufferObject();
		~GLBufferObject();
	};

	struct GLVertexBufferObject : public GLBufferObject
	{
		GLVertexBufferObject(const std::vector<Vertex>& data);
		~GLVertexBufferObject();

	private:
		std::vector<Vertex> data;
	};

	struct GLElementBufferObject : public GLBufferObject
	{
		GLElementBufferObject(const std::vector<GLuint>& data);
		~GLElementBufferObject();

	private:
		std::vector<GLuint> data;
	};


}