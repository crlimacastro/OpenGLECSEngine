#pragma once
#include <entt/entt.hpp>

struct TransformController
{
	float moveSpeed = 8.f;
	float rotateSpeed = 128.f;
};

void UpdateTransformsWithController(entt::registry& registry);
