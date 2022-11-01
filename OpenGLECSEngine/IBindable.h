#pragma once
#include <cstdint>

namespace fae
{
	struct IBindable
	{
		virtual operator uint32_t() const = 0;
		virtual IBindable& Bind() = 0;
		virtual IBindable& Unbind() = 0;
	};
}
