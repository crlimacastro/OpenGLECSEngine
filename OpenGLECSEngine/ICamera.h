#pragma once
#include <glm/glm.hpp>

struct ICamera
{
	virtual glm::mat4 GetProjectionMatrix(float aspectRatio) const = 0;
};