#pragma once
#include <GL/glew.h>
#include "IBindable.h"

namespace fae
{
	struct GLObject : virtual public IBindable
	{
		GLuint id = 0;
		virtual operator uint32_t() const override { return id; }
	};
}
