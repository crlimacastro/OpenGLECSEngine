#pragma once
#include <entt/entt.hpp>

struct CameraController
{
	float moveSpeed = 8.f;
	float sensitivity = 128.f;
};

void UpdateCameraController(entt::registry& registry);
