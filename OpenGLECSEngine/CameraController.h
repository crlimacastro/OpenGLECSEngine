#pragma once
#include <entt/entt.hpp>

struct CameraController
{
	float moveSpeed = 10.f;
	float sensitivity = 1.f;
};

void UpdateCameraController(entt::registry& registry);
