#pragma once
#include "ICamera.h"

namespace fae
{
	struct PerspectiveCamera : public ICamera
	{
		float fov = 90;
		float nearPlane = .1f;
		float farPlane = 1000;

		// Inherited via ICamera
		virtual glm::mat4 GetProjectionMatrix(float aspectRatio) const override;
	};
}