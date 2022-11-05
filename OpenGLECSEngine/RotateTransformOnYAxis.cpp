#include "RotateTransformOnYAxis.h"
#include "time.h"
#include "transforms.h"
#include <glm/glm.hpp>

using namespace fae;

void UpdateRotateTransformOnYAxis(entt::registry& registry)
{
	auto& time = registry.ctx().at<Time>();

	for (auto [entity, transform, rotate] : registry.view<LocalTransform, const RotateTransformOnYAxis>().each())
	{
		transform.rotation *= glm::quat({ 0, glm::radians(rotate.speed * time.GetDeltaSeconds()), 0 });
	}
}
