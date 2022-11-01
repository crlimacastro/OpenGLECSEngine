#pragma once
#include <entt/entt.hpp>

struct TransformController
{
	float moveSpeed;
	float rotateSpeed;
};

void UpdateTransformsWithController(entt::registry& registry);
