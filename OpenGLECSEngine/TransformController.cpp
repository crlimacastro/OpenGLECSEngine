#include "TransformController.h"
#include "InputPlugin.h"
#include "transforms.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace fae;

void UpdateTransformsWithController(entt::registry& registry)
{
	auto& input = registry.ctx().at<Input>();

	for (auto [entity, transform, controller] : registry.view<GlobalTransform, const TransformController>().each())
	{
		// get direction
		glm::vec3 direction{ 0 };
		if (input.IsPressed(GLFW_KEY_W)) {
			direction.z += 1;
		}
		if (input.IsPressed(GLFW_KEY_S)) {
			direction.z -= 1;
		}
		if (input.IsPressed(GLFW_KEY_A)) {
			direction.x += 1;
		}
		if (input.IsPressed(GLFW_KEY_D)) {
			direction.x -= 1;
		}
		if (input.IsPressed(GLFW_KEY_LEFT_SHIFT)) {
			direction.y += 1;
		}
		if (input.IsPressed(GLFW_KEY_LEFT_CONTROL)) {
			direction.y -= 1;
		}


		// normalize it
		if (glm::length(direction) > 0) {
			direction = glm::normalize(direction);
		}

		// update position
		if (glm::length(direction) > 0) {
			auto test = transform.rotation * direction;
			auto x = 3;
		}
		transform.position += transform.rotation * direction * controller.moveSpeed;

		// get rotate direction
		int rotate = 0;
		if (input.IsPressed(GLFW_KEY_Q)) {
			rotate += 1;
		}
		if (input.IsPressed(GLFW_KEY_E)) {
			rotate -= 1;
		}

		transform.rotation *= glm::quat({ 0, rotate * glm::radians(controller.rotateSpeed), 0 });
	}
}
