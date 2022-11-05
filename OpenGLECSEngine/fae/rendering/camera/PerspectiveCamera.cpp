#include "PerspectiveCamera.h"
#include <glm/ext/matrix_clip_space.hpp>

glm::mat4 fae::PerspectiveCamera::GetProjectionMatrix(float aspectRatio) const
{
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);;
}