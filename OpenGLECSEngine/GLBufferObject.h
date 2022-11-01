#pragma once
#include "GLObject.h"

namespace fae
{
	struct GLBufferObject : public GLObject
	{
		GLBufferObject();
		~GLBufferObject();

		virtual GLBufferObject& Bind() = 0;
		virtual GLBufferObject& Unbind() = 0;
	};
}
