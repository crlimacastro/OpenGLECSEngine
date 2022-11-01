#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Texture.h"
#include "IShaderProgram.h"

namespace fae
{
	struct Material
	{
		IShaderProgram& shader;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		Texture& diffuseTex;
		Texture& specularTex;

		void Send() const;
	};
}

