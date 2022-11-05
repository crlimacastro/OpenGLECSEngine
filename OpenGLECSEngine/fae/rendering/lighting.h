#pragma once
#include "../App.h"
#include <glm/glm.hpp>

namespace fae
{
	struct Light
	{
		float intensity = 1.f;
		glm::vec3 color = { 1.f, 1.f, 1.f };

		float constant = 1.f;
		float linear = .045f;
		float quadratic = .0075f;
	};

	// Components

	struct PointLight : public Light
	{

	};

	// Systems

	void UpdatePointLightsWithTransforms(entt::registry& registry);


	// Plugins

	void LightingPlugin(App& app);
}
