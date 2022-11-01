#pragma once
#include <vector>
#include "GLBufferObject.h"

namespace fae
{
	struct GLElementBufferObject : public GLBufferObject
	{
		GLElementBufferObject(const std::vector<GLuint>& data);
		~GLElementBufferObject();

		// Inherited via GLBufferObject
		virtual GLBufferObject& Bind() override;
		virtual GLBufferObject& Unbind() override;

	private:
		std::vector<GLuint> data;
	};
}
