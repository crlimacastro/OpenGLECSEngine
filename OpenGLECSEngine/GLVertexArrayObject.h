#pragma once
#include "GLObject.h"
#include "IBindable.h"

namespace fae
{
	struct GLVertexArrayObject : public GLObject
	{
		GLVertexArrayObject();
		~GLVertexArrayObject();

		virtual IBindable& Bind() override;
		virtual IBindable& Unbind() override;
	};
}
