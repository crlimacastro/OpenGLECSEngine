#pragma once
#include "GLObject.h"
#include "IShaderProgram.h"

namespace fae
{
	struct GLShaderProgram : public GLObject, public IShaderProgram
	{
		GLShaderProgram();
		~GLShaderProgram();

		// Inherited via IBindable
		virtual operator uint32_t() const override;
		virtual IBindable& Bind() override;
		virtual IBindable& Unbind() override;

		// Inherited via IShaderProgram
		virtual IShaderProgram& LoadVertexFromSource(const char* source) override;
		virtual IShaderProgram& LoadFragmentFromSource(const char* source) override;
		virtual IShaderProgram& LoadGeometryFromSource(const char* source) override;

		virtual IShaderProgram& LoadVertexFromFile(const char* path) override;
		virtual IShaderProgram& LoadFragmentFromFile(const char* path) override;
		virtual IShaderProgram& LoadGeometryFromFile(const char* path) override;

		virtual IShaderProgram& Link() override;

		virtual IShaderProgram& set1i(const char* name, int value) override;
		virtual IShaderProgram& set1f(const char* name, float value) override;
		virtual IShaderProgram& setv2f(const char* name, glm::fvec2 value) override;
		virtual IShaderProgram& setv3f(const char* name, glm::fvec3 value) override;
		virtual IShaderProgram& setm3f(const char* name, glm::mat3 value, bool transpose) override;
		virtual IShaderProgram& setm4f(const char* name, glm::mat4 value, bool transpose) override;

	private:
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;
		GLuint geometryShader = 0;
	};
}
