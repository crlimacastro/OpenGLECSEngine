#pragma once
#include <vector>
#include "GLBufferObject.h"
#include "Vertex.h"

namespace fae
{
	struct GLVertexBufferObject : public GLBufferObject
	{
		GLVertexBufferObject(const std::vector<Vertex>& data);
		~GLVertexBufferObject();

		// Inherited via GLBufferObject
		virtual GLBufferObject& Bind() override;
		virtual GLBufferObject& Unbind() override;

	private:
		std::vector<Vertex> data;
	};
}
