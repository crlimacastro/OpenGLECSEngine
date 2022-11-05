#pragma once
#include <entt/entt.hpp>

struct RotateTransformOnYAxis
{
	float speed = 100.f;
};

void UpdateRotateTransformOnYAxis(entt::registry& registry);