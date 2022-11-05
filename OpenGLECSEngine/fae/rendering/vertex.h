#pragma once
#include <glm/glm.hpp>

namespace fae
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 uvcoord;
		glm::vec3 normal;
	};
}
