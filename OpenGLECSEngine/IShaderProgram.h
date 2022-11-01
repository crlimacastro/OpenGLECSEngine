#pragma once
#include <glm/glm.hpp>
#include "IBindable.h"

namespace fae
{
	struct IShaderProgram : virtual public IBindable
	{
		virtual IShaderProgram& LoadVertexFromSource(const char* source) = 0;
		virtual IShaderProgram& LoadFragmentFromSource(const char* source) = 0;
		virtual IShaderProgram& LoadGeometryFromSource(const char* source) = 0;

		virtual IShaderProgram& LoadVertexFromFile(const char* path) = 0;
		virtual IShaderProgram& LoadFragmentFromFile(const char* path) = 0;
		virtual IShaderProgram& LoadGeometryFromFile(const char* path) = 0;

		/// <summary>
		/// Links & attaches all shaders together
		/// </summary>
		/// <returns></returns>
		virtual IShaderProgram& Link() = 0;

		// Set uniform methods

		virtual IShaderProgram& set1i(const char* name, int value) = 0;
		virtual IShaderProgram& set1f(const char* name, float value) = 0;
		virtual IShaderProgram& setv2f(const char* name, glm::fvec2 value) = 0;
		virtual IShaderProgram& setv3f(const char* name, glm::fvec3 value) = 0;
		virtual IShaderProgram& setm3f(const char* name, glm::fmat3 value, bool transpose = false) = 0;
		virtual IShaderProgram& setm4f(const char* name, glm::fmat4 value, bool transpose = false) = 0;
	};
}
