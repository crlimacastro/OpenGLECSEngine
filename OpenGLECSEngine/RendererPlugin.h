#pragma once
#include <vector>
#include <string_view>
#include <GL/glew.h>
#include "Vertex.h"
#include "App.h"

namespace gfe {
	/// <summary>
	/// OpenGL Object
	/// </summary>
	struct GLO {
		GLuint id;
		operator GLuint () { return id; }
		operator const GLuint() const { return id; }
		virtual GLO& Bind() = 0;
		virtual GLO& Unbind() = 0;
	};

	struct Shader : public GLO
	{
		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		~Shader();
		GLO& Bind() override;
		GLO& Unbind() override;

	private:
		static GLuint CompileShaderFromFile(std::string_view path, GLenum shaderType);
	};

	/// <summary>
/// Vertex Array Object
/// </summary>
	struct VAO : public GLO {
		VAO()
		{
			glCreateVertexArrays(1, &id);
		}
		~VAO()
		{
			GLint id;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
			if (id == this->id)
			{
				Unbind();
			}
			glDeleteVertexArrays(1, &this->id);
		}
		GLO& Bind() override
		{
			glBindVertexArray(id);
			return *this;
		}
		GLO& Unbind() override
		{
			GLint id;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
			if (id != this->id)
			{
				return *this;
			}
			glBindVertexArray(0);
			return *this;
		}
	};

	/// <summary>
	/// OpenGL Buffer Object
	/// </summary>
	struct GLB : public GLO {
		GLB()
		{
			glGenBuffers(1, &id);
		}
		~GLB()
		{
			glDeleteBuffers(1, &id);
		}
	};

	/// <summary>
	/// Vertex Buffer Object
	/// </summary>
	struct VBO : public GLB {
		VBO(std::vector<Vertex>& data) : GLB()
		{
			Bind();
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
			Unbind();
		}

		GLO& Bind() override
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			return *this;
		}

		GLO& Unbind() override
		{
			GLint id;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
			if (id != this->id)
			{
				return *this;
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return *this;
		}

		~VBO()
		{
			GLint id;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
			if (id == this->id)
			{
				Unbind();
			}
		}
	};

	/// <summary>
	/// Element Buffer Object
	/// </summary>
	struct EBO : public GLB {
		EBO(std::vector<GLuint>& data) : GLB()
		{
			Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
			Unbind();
		}

		GLO& Bind() override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			return *this;
		}

		GLO& Unbind() override
		{
			GLint id;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);
			if (id != this->id)
			{
				return *this;
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			return *this;
		}

		~EBO()
		{
			GLint id;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);
			if (id == this->id)
			{
				Unbind();
			}
		}
	};

	struct Renderer
	{
		Shader& currentShader;
		VAO& currentVAO;
	};

	void RendererPlugin(App& app);
}